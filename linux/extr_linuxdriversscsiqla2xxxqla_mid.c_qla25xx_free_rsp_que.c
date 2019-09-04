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
typedef  int uint16_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct rsp_que {int id; int length; scalar_t__ dma; int /*<<< orphan*/ * ring; TYPE_1__* msix; } ;
struct qla_hw_data {int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  rsp_qid_map; int /*<<< orphan*/ ** rsp_q_map; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  response_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * handle; scalar_t__ in_use; scalar_t__ have_irq; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rsp_que*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla25xx_free_rsp_que(struct scsi_qla_host *vha, struct rsp_que *rsp)
{
	struct qla_hw_data *ha = vha->hw;
	uint16_t que_id = rsp->id;

	if (rsp->msix && rsp->msix->have_irq) {
		free_irq(rsp->msix->vector, rsp->msix->handle);
		rsp->msix->have_irq = 0;
		rsp->msix->in_use = 0;
		rsp->msix->handle = NULL;
	}
	dma_free_coherent(&ha->pdev->dev, (rsp->length + 1) *
		sizeof(response_t), rsp->ring, rsp->dma);
	rsp->ring = NULL;
	rsp->dma = 0;
	if (que_id) {
		ha->rsp_q_map[que_id] = NULL;
		mutex_lock(&ha->vport_lock);
		clear_bit(que_id, ha->rsp_qid_map);
		mutex_unlock(&ha->vport_lock);
	}
	kfree(rsp);
	rsp = NULL;
}