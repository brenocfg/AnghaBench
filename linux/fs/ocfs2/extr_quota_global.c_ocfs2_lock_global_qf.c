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
struct ocfs2_mem_dqinfo {int /*<<< orphan*/  dqi_gqinode; struct buffer_head* dqi_gqi_bh; int /*<<< orphan*/  dqi_gqi_count; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (int /*<<< orphan*/ ,struct buffer_head**,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_lock_global_qf(struct ocfs2_mem_dqinfo *oinfo, int ex)
{
	int status;
	struct buffer_head *bh = NULL;

	status = ocfs2_inode_lock(oinfo->dqi_gqinode, &bh, ex);
	if (status < 0)
		return status;
	spin_lock(&dq_data_lock);
	if (!oinfo->dqi_gqi_count++)
		oinfo->dqi_gqi_bh = bh;
	else
		WARN_ON(bh != oinfo->dqi_gqi_bh);
	spin_unlock(&dq_data_lock);
	if (ex) {
		inode_lock(oinfo->dqi_gqinode);
		down_write(&OCFS2_I(oinfo->dqi_gqinode)->ip_alloc_sem);
	} else {
		down_read(&OCFS2_I(oinfo->dqi_gqinode)->ip_alloc_sem);
	}
	return 0;
}