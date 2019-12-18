#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_inode_info {int /*<<< orphan*/  i_datasync_tid; int /*<<< orphan*/  i_sync_tid; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {TYPE_1__* h_transaction; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  t_tid; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 

__attribute__((used)) static inline void ocfs2_update_inode_fsync_trans(handle_t *handle,
						  struct inode *inode,
						  int datasync)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	oi->i_sync_tid = handle->h_transaction->t_tid;
	if (datasync)
		oi->i_datasync_tid = handle->h_transaction->t_tid;
}