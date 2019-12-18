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
struct pstore_info {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* s_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct pstore_info* psinfo ; 
 int /*<<< orphan*/  pstore_get_backend_records (struct pstore_info*,struct dentry*,int) ; 
 TYPE_1__* pstore_sb ; 

void pstore_get_records(int quiet)
{
	struct pstore_info *psi = psinfo;
	struct dentry *root;

	if (!psi || !pstore_sb)
		return;

	root = pstore_sb->s_root;

	inode_lock(d_inode(root));
	pstore_get_backend_records(psi, root, quiet);
	inode_unlock(d_inode(root));
}