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
struct inode {TYPE_1__* i_sb; } ;
struct fid {int /*<<< orphan*/  raw; } ;
struct export_operations {int (* encode_fh ) (struct inode*,int /*<<< orphan*/ ,int*,struct inode*) ;} ;
struct TYPE_2__ {struct export_operations* s_export_op; } ;

/* Variables and functions */
 int export_encode_fh (struct inode*,struct fid*,int*,struct inode*) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ ,int*,struct inode*) ; 

int exportfs_encode_inode_fh(struct inode *inode, struct fid *fid,
			     int *max_len, struct inode *parent)
{
	const struct export_operations *nop = inode->i_sb->s_export_op;

	if (nop && nop->encode_fh)
		return nop->encode_fh(inode, fid->raw, max_len, parent);

	return export_encode_fh(inode, fid, max_len, parent);
}