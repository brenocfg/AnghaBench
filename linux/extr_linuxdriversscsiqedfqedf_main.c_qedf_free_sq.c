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
struct qedf_rport {int /*<<< orphan*/  sq_dma; scalar_t__ sq; int /*<<< orphan*/  sq_mem_size; int /*<<< orphan*/  sq_pbl_dma; scalar_t__ sq_pbl; int /*<<< orphan*/  sq_pbl_size; } ;
struct qedf_ctx {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_free_sq(struct qedf_ctx *qedf, struct qedf_rport *fcport)
{
	if (fcport->sq_pbl)
		dma_free_coherent(&qedf->pdev->dev, fcport->sq_pbl_size,
		    fcport->sq_pbl, fcport->sq_pbl_dma);
	if (fcport->sq)
		dma_free_coherent(&qedf->pdev->dev, fcport->sq_mem_size,
		    fcport->sq, fcport->sq_dma);
}