#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct svc_fh {int fh_locked; int /*<<< orphan*/  fh_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_post_wcc (struct svc_fh*) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fh_unlock(struct svc_fh *fhp)
{
	if (fhp->fh_locked) {
		fill_post_wcc(fhp);
		inode_unlock(d_inode(fhp->fh_dentry));
		fhp->fh_locked = false;
	}
}