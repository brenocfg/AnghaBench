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
typedef  size_t u32 ;
struct TYPE_4__ {struct bnx2i_conn** conn_cid_tbl; } ;
struct bnx2i_hba {TYPE_2__ cid_que; } ;
struct bnx2i_conn {TYPE_1__* cls_conn; } ;
struct TYPE_3__ {int /*<<< orphan*/  dd_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KERN_ALERT ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int bnx2i_bind_conn_to_iscsi_cid(struct bnx2i_hba *hba,
					struct bnx2i_conn *bnx2i_conn,
					u32 iscsi_cid)
{
	if (hba && hba->cid_que.conn_cid_tbl[iscsi_cid]) {
		iscsi_conn_printk(KERN_ALERT, bnx2i_conn->cls_conn->dd_data,
				 "conn bind - entry #%d not free\n", iscsi_cid);
		return -EBUSY;
	}

	hba->cid_que.conn_cid_tbl[iscsi_cid] = bnx2i_conn;
	return 0;
}