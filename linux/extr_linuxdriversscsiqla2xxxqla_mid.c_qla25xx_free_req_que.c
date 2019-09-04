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
typedef  int uint16_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct req_que {int id; int length; struct req_que* outstanding_cmds; scalar_t__ dma; int /*<<< orphan*/ * ring; } ;
struct qla_hw_data {int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  req_qid_map; int /*<<< orphan*/ ** req_q_map; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  request_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct req_que*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla25xx_free_req_que(struct scsi_qla_host *vha, struct req_que *req)
{
	struct qla_hw_data *ha = vha->hw;
	uint16_t que_id = req->id;

	dma_free_coherent(&ha->pdev->dev, (req->length + 1) *
		sizeof(request_t), req->ring, req->dma);
	req->ring = NULL;
	req->dma = 0;
	if (que_id) {
		ha->req_q_map[que_id] = NULL;
		mutex_lock(&ha->vport_lock);
		clear_bit(que_id, ha->req_qid_map);
		mutex_unlock(&ha->vport_lock);
	}
	kfree(req->outstanding_cmds);
	kfree(req);
	req = NULL;
}