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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* d_alloc_anon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

struct dentry *d_make_root(struct inode *root_inode)
{
	struct dentry *res = NULL;

	if (root_inode) {
		res = d_alloc_anon(root_inode->i_sb);
		if (res)
			d_instantiate(res, root_inode);
		else
			iput(root_inode);
	}
	return res;
}