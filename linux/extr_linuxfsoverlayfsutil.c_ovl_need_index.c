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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {int i_nlink; } ;

/* Variables and functions */
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 struct dentry* ovl_dentry_lower (struct dentry*) ; 
 scalar_t__ ovl_index_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_indexdir (int /*<<< orphan*/ ) ; 

bool ovl_need_index(struct dentry *dentry)
{
	struct dentry *lower = ovl_dentry_lower(dentry);

	if (!lower || !ovl_indexdir(dentry->d_sb))
		return false;

	/* Index all files for NFS export and consistency verification */
	if (ovl_index_all(dentry->d_sb))
		return true;

	/* Index only lower hardlinks on copy up */
	if (!d_is_dir(lower) && d_inode(lower)->i_nlink > 1)
		return true;

	return false;
}