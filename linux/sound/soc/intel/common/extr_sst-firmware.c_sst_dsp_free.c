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
struct sst_dsp {int /*<<< orphan*/  dma; TYPE_1__* ops; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct sst_dsp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sst_dsp*) ; 
 int /*<<< orphan*/  sst_dma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sst_dsp*) ; 

void sst_dsp_free(struct sst_dsp *sst)
{
	free_irq(sst->irq, sst);
	if (sst->ops->free)
		sst->ops->free(sst);

	sst_dma_free(sst->dma);
}