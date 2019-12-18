#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* time64_t ;
struct orangefs_inode_s {int attr_valid; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct inode {int /*<<< orphan*/  i_mode; TYPE_2__ i_mtime; TYPE_1__ i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct ORANGEFS_sys_attr_s {int /*<<< orphan*/  mask; int /*<<< orphan*/  perms; void* mtime; void* atime; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_CTIME ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  GOSSIP_UTILS_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_ATIME ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_ATIME_SET ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_CTIME ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_GID ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_MTIME ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_MTIME_SET ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_PERM ; 
 int /*<<< orphan*/  ORANGEFS_ATTR_SYS_UID ; 
 struct orangefs_inode_s* ORANGEFS_I (struct inode*) ; 
 int /*<<< orphan*/  ORANGEFS_util_translate_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static inline void copy_attributes_from_inode(struct inode *inode,
    struct ORANGEFS_sys_attr_s *attrs)
{
	struct orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	attrs->mask = 0;
	if (orangefs_inode->attr_valid & ATTR_UID) {
		attrs->owner = from_kuid(&init_user_ns, inode->i_uid);
		attrs->mask |= ORANGEFS_ATTR_SYS_UID;
		gossip_debug(GOSSIP_UTILS_DEBUG, "(UID) %d\n", attrs->owner);
	}
	if (orangefs_inode->attr_valid & ATTR_GID) {
		attrs->group = from_kgid(&init_user_ns, inode->i_gid);
		attrs->mask |= ORANGEFS_ATTR_SYS_GID;
		gossip_debug(GOSSIP_UTILS_DEBUG, "(GID) %d\n", attrs->group);
	}

	if (orangefs_inode->attr_valid & ATTR_ATIME) {
		attrs->mask |= ORANGEFS_ATTR_SYS_ATIME;
		if (orangefs_inode->attr_valid & ATTR_ATIME_SET) {
			attrs->atime = (time64_t)inode->i_atime.tv_sec;
			attrs->mask |= ORANGEFS_ATTR_SYS_ATIME_SET;
		}
	}
	if (orangefs_inode->attr_valid & ATTR_MTIME) {
		attrs->mask |= ORANGEFS_ATTR_SYS_MTIME;
		if (orangefs_inode->attr_valid & ATTR_MTIME_SET) {
			attrs->mtime = (time64_t)inode->i_mtime.tv_sec;
			attrs->mask |= ORANGEFS_ATTR_SYS_MTIME_SET;
		}
	}
	if (orangefs_inode->attr_valid & ATTR_CTIME)
		attrs->mask |= ORANGEFS_ATTR_SYS_CTIME;

	/*
	 * ORANGEFS cannot set size with a setattr operation. Probably not
	 * likely to be requested through the VFS, but just in case, don't
	 * worry about ATTR_SIZE
	 */

	if (orangefs_inode->attr_valid & ATTR_MODE) {
		attrs->perms = ORANGEFS_util_translate_mode(inode->i_mode);
		attrs->mask |= ORANGEFS_ATTR_SYS_PERM;
	}
}