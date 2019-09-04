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
typedef  int /*<<< orphan*/  umode_t ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; TYPE_1__ i_data; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {scalar_t__ i_alloc_type; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 TYPE_2__* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int udf_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  udf_adinicb_aops ; 
 int /*<<< orphan*/  udf_aops ; 
 int /*<<< orphan*/  udf_file_inode_operations ; 
 int /*<<< orphan*/  udf_file_operations ; 
 struct inode* udf_new_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_create(struct inode *dir, struct dentry *dentry, umode_t mode,
		      bool excl)
{
	struct inode *inode = udf_new_inode(dir, mode);

	if (IS_ERR(inode))
		return PTR_ERR(inode);

	if (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		inode->i_data.a_ops = &udf_adinicb_aops;
	else
		inode->i_data.a_ops = &udf_aops;
	inode->i_op = &udf_file_inode_operations;
	inode->i_fop = &udf_file_operations;
	mark_inode_dirty(inode);

	return udf_add_nondir(dentry, inode);
}