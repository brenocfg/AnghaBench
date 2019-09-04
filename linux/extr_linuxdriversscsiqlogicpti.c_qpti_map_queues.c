#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qlogicpti {scalar_t__ res_dvma; scalar_t__ req_dvma; int /*<<< orphan*/ * req_cpu; int /*<<< orphan*/ * res_cpu; struct platform_device* op; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int RES_QUEUE_LEN ;
typedef  int QLOGICPTI_REQ_QUEUE_LEN ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QUEUE_ENTRY_LEN ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int qpti_map_queues(struct qlogicpti *qpti)
{
	struct platform_device *op = qpti->op;

#define QSIZE(entries)	(((entries) + 1) * QUEUE_ENTRY_LEN)
	qpti->res_cpu = dma_alloc_coherent(&op->dev,
					   QSIZE(RES_QUEUE_LEN),
					   &qpti->res_dvma, GFP_ATOMIC);
	if (qpti->res_cpu == NULL ||
	    qpti->res_dvma == 0) {
		printk("QPTI: Cannot map response queue.\n");
		return -1;
	}

	qpti->req_cpu = dma_alloc_coherent(&op->dev,
					   QSIZE(QLOGICPTI_REQ_QUEUE_LEN),
					   &qpti->req_dvma, GFP_ATOMIC);
	if (qpti->req_cpu == NULL ||
	    qpti->req_dvma == 0) {
		dma_free_coherent(&op->dev, QSIZE(RES_QUEUE_LEN),
				  qpti->res_cpu, qpti->res_dvma);
		printk("QPTI: Cannot map request queue.\n");
		return -1;
	}
	memset(qpti->res_cpu, 0, QSIZE(RES_QUEUE_LEN));
	memset(qpti->req_cpu, 0, QSIZE(QLOGICPTI_REQ_QUEUE_LEN));
	return 0;
}