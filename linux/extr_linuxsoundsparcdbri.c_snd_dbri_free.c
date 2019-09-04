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
struct snd_dbri {int /*<<< orphan*/  dma_dvma; scalar_t__ dma; TYPE_1__* op; int /*<<< orphan*/  regs_size; scalar_t__ regs; scalar_t__ irq; } ;
struct dbri_dma {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_GEN ; 
 int /*<<< orphan*/  dbri_reset (struct snd_dbri*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_dbri*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_dbri_free(struct snd_dbri *dbri)
{
	dprintk(D_GEN, "snd_dbri_free\n");
	dbri_reset(dbri);

	if (dbri->irq)
		free_irq(dbri->irq, dbri);

	if (dbri->regs)
		of_iounmap(&dbri->op->resource[0], dbri->regs, dbri->regs_size);

	if (dbri->dma)
		dma_free_coherent(&dbri->op->dev,
				  sizeof(struct dbri_dma),
				  (void *)dbri->dma, dbri->dma_dvma);
}