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
struct omap_mcbsp {int free; int /*<<< orphan*/  lock; int /*<<< orphan*/ * reg_cache; scalar_t__ id; int /*<<< orphan*/  dev; scalar_t__ tx_irq; scalar_t__ rx_irq; scalar_t__ irq; TYPE_2__* pdata; } ;
struct TYPE_4__ {scalar_t__ has_wakeup; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQEN ; 
 int /*<<< orphan*/  MCBSP_CLKS_PRCM_SRC ; 
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAKEUPEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mcbsp_omap1 () ; 
 int /*<<< orphan*/  omap2_mcbsp_set_clks_src (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void omap_mcbsp_free(struct omap_mcbsp *mcbsp)
{
	void *reg_cache;

	if(mcbsp->pdata->ops && mcbsp->pdata->ops->free)
		mcbsp->pdata->ops->free(mcbsp->id - 1);

	/* Disable wakeup behavior */
	if (mcbsp->pdata->has_wakeup)
		MCBSP_WRITE(mcbsp, WAKEUPEN, 0);

	/* Disable interrupt requests */
	if (mcbsp->irq)
		MCBSP_WRITE(mcbsp, IRQEN, 0);

	if (mcbsp->irq) {
		free_irq(mcbsp->irq, (void *)mcbsp);
	} else {
		free_irq(mcbsp->rx_irq, (void *)mcbsp);
		free_irq(mcbsp->tx_irq, (void *)mcbsp);
	}

	reg_cache = mcbsp->reg_cache;

	/*
	 * Select CLKS source from internal source unconditionally before
	 * marking the McBSP port as free.
	 * If the external clock source via MCBSP_CLKS pin has been selected the
	 * system will refuse to enter idle if the CLKS pin source is not reset
	 * back to internal source.
	 */
	if (!mcbsp_omap1())
		omap2_mcbsp_set_clks_src(mcbsp, MCBSP_CLKS_PRCM_SRC);

	spin_lock(&mcbsp->lock);
	if (mcbsp->free)
		dev_err(mcbsp->dev, "McBSP%d was not reserved\n", mcbsp->id);
	else
		mcbsp->free = true;
	mcbsp->reg_cache = NULL;
	spin_unlock(&mcbsp->lock);

	kfree(reg_cache);
}