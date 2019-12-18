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
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; } ;
struct afs_vnode {int /*<<< orphan*/  cb_s_break; int /*<<< orphan*/  cb_v_break; int /*<<< orphan*/  volume; TYPE_1__ fid; } ;
struct afs_iget_data {TYPE_1__ fid; int /*<<< orphan*/  cb_s_break; int /*<<< orphan*/  cb_v_break; int /*<<< orphan*/  volume; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 

__attribute__((used)) static int afs_iget5_set(struct inode *inode, void *opaque)
{
	struct afs_iget_data *iget_data = opaque;
	struct afs_vnode *vnode = AFS_FS_I(inode);

	vnode->fid		= iget_data->fid;
	vnode->volume		= iget_data->volume;
	vnode->cb_v_break	= iget_data->cb_v_break;
	vnode->cb_s_break	= iget_data->cb_s_break;

	/* YFS supports 96-bit vnode IDs, but Linux only supports
	 * 64-bit inode numbers.
	 */
	inode->i_ino		= iget_data->fid.vnode;
	inode->i_generation	= iget_data->fid.unique;
	return 0;
}