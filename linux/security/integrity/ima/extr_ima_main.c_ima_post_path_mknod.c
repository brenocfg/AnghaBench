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
struct integrity_iint_cache {int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CHECK ; 
 int /*<<< orphan*/  IMA_NEW_FILE ; 
 int /*<<< orphan*/  MAY_ACCESS ; 
 int ima_must_appraise (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct integrity_iint_cache* integrity_inode_get (struct inode*) ; 

void ima_post_path_mknod(struct dentry *dentry)
{
	struct integrity_iint_cache *iint;
	struct inode *inode = dentry->d_inode;
	int must_appraise;

	must_appraise = ima_must_appraise(inode, MAY_ACCESS, FILE_CHECK);
	if (!must_appraise)
		return;

	/* Nothing to do if we can't allocate memory */
	iint = integrity_inode_get(inode);
	if (!iint)
		return;

	/* needed for re-opening empty files */
	iint->flags |= IMA_NEW_FILE;
}