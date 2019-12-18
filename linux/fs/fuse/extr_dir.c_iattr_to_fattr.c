#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct iattr {unsigned int ia_valid; TYPE_3__ ia_ctime; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; int /*<<< orphan*/  ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
struct fuse_setattr_in {int /*<<< orphan*/  ctimensec; int /*<<< orphan*/  ctime; int /*<<< orphan*/  valid; int /*<<< orphan*/  mtimensec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atimensec; int /*<<< orphan*/  atime; int /*<<< orphan*/  size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct fuse_conn {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_ATIME_SET ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_MTIME_SET ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  FATTR_ATIME ; 
 int /*<<< orphan*/  FATTR_ATIME_NOW ; 
 int /*<<< orphan*/  FATTR_CTIME ; 
 int /*<<< orphan*/  FATTR_GID ; 
 int /*<<< orphan*/  FATTR_MODE ; 
 int /*<<< orphan*/  FATTR_MTIME ; 
 int /*<<< orphan*/  FATTR_MTIME_NOW ; 
 int /*<<< orphan*/  FATTR_SIZE ; 
 int /*<<< orphan*/  FATTR_UID ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ update_mtime (unsigned int,int) ; 

__attribute__((used)) static void iattr_to_fattr(struct fuse_conn *fc, struct iattr *iattr,
			   struct fuse_setattr_in *arg, bool trust_local_cmtime)
{
	unsigned ivalid = iattr->ia_valid;

	if (ivalid & ATTR_MODE)
		arg->valid |= FATTR_MODE,   arg->mode = iattr->ia_mode;
	if (ivalid & ATTR_UID)
		arg->valid |= FATTR_UID,    arg->uid = from_kuid(fc->user_ns, iattr->ia_uid);
	if (ivalid & ATTR_GID)
		arg->valid |= FATTR_GID,    arg->gid = from_kgid(fc->user_ns, iattr->ia_gid);
	if (ivalid & ATTR_SIZE)
		arg->valid |= FATTR_SIZE,   arg->size = iattr->ia_size;
	if (ivalid & ATTR_ATIME) {
		arg->valid |= FATTR_ATIME;
		arg->atime = iattr->ia_atime.tv_sec;
		arg->atimensec = iattr->ia_atime.tv_nsec;
		if (!(ivalid & ATTR_ATIME_SET))
			arg->valid |= FATTR_ATIME_NOW;
	}
	if ((ivalid & ATTR_MTIME) && update_mtime(ivalid, trust_local_cmtime)) {
		arg->valid |= FATTR_MTIME;
		arg->mtime = iattr->ia_mtime.tv_sec;
		arg->mtimensec = iattr->ia_mtime.tv_nsec;
		if (!(ivalid & ATTR_MTIME_SET) && !trust_local_cmtime)
			arg->valid |= FATTR_MTIME_NOW;
	}
	if ((ivalid & ATTR_CTIME) && trust_local_cmtime) {
		arg->valid |= FATTR_CTIME;
		arg->ctime = iattr->ia_ctime.tv_sec;
		arg->ctimensec = iattr->ia_ctime.tv_nsec;
	}
}