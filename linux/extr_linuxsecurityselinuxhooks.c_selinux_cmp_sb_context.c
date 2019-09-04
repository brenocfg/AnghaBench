#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct superblock_security_struct {char flags; scalar_t__ sid; scalar_t__ mntpoint_sid; scalar_t__ def_sid; } ;
struct super_block {TYPE_1__* s_type; int /*<<< orphan*/  s_id; int /*<<< orphan*/  s_root; struct superblock_security_struct* s_security; } ;
struct inode_security_struct {scalar_t__ sid; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char CONTEXT_MNT ; 
 char DEFCONTEXT_MNT ; 
 int EBUSY ; 
 char FSCONTEXT_MNT ; 
 char ROOTCONTEXT_MNT ; 
 char SE_MNTMASK ; 
 struct inode_security_struct* backing_inode_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_cmp_sb_context(const struct super_block *oldsb,
				    const struct super_block *newsb)
{
	struct superblock_security_struct *old = oldsb->s_security;
	struct superblock_security_struct *new = newsb->s_security;
	char oldflags = old->flags & SE_MNTMASK;
	char newflags = new->flags & SE_MNTMASK;

	if (oldflags != newflags)
		goto mismatch;
	if ((oldflags & FSCONTEXT_MNT) && old->sid != new->sid)
		goto mismatch;
	if ((oldflags & CONTEXT_MNT) && old->mntpoint_sid != new->mntpoint_sid)
		goto mismatch;
	if ((oldflags & DEFCONTEXT_MNT) && old->def_sid != new->def_sid)
		goto mismatch;
	if (oldflags & ROOTCONTEXT_MNT) {
		struct inode_security_struct *oldroot = backing_inode_security(oldsb->s_root);
		struct inode_security_struct *newroot = backing_inode_security(newsb->s_root);
		if (oldroot->sid != newroot->sid)
			goto mismatch;
	}
	return 0;
mismatch:
	pr_warn("SELinux: mount invalid.  Same superblock, "
			    "different security settings for (dev %s, "
			    "type %s)\n", newsb->s_id, newsb->s_type->name);
	return -EBUSY;
}