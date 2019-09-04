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
typedef  size_t u16 ;
struct TYPE_2__ {int cid_q_prod_idx; size_t* cid_que; int cid_q_max_idx; int /*<<< orphan*/ ** conn_cid_tbl; int /*<<< orphan*/  cid_free_cnt; } ;
struct bnx2i_hba {TYPE_1__ cid_que; } ;

/* Variables and functions */

__attribute__((used)) static void bnx2i_free_iscsi_cid(struct bnx2i_hba *hba, u16 iscsi_cid)
{
	int idx;

	if (iscsi_cid == (u16) -1)
		return;

	hba->cid_que.cid_free_cnt++;

	idx = hba->cid_que.cid_q_prod_idx;
	hba->cid_que.cid_que[idx] = iscsi_cid;
	hba->cid_que.conn_cid_tbl[iscsi_cid] = NULL;
	hba->cid_que.cid_q_prod_idx++;
	if (hba->cid_que.cid_q_prod_idx == hba->cid_que.cid_q_max_idx)
		hba->cid_que.cid_q_prod_idx = 0;
}