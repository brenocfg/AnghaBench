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
struct integrity_iint_cache {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  ima_check_last_writer (struct integrity_iint_cache*,struct inode*,struct file*) ; 
 int /*<<< orphan*/  ima_policy_flag ; 
 struct integrity_iint_cache* integrity_iint_find (struct inode*) ; 

void ima_file_free(struct file *file)
{
	struct inode *inode = file_inode(file);
	struct integrity_iint_cache *iint;

	if (!ima_policy_flag || !S_ISREG(inode->i_mode))
		return;

	iint = integrity_iint_find(inode);
	if (!iint)
		return;

	ima_check_last_writer(iint, inode, file);
}