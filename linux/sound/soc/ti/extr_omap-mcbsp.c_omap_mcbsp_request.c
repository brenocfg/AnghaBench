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
struct omap_mcbsp {int free; int /*<<< orphan*/  lock; int /*<<< orphan*/ * reg_cache; TYPE_2__* pdata; scalar_t__ id; scalar_t__ tx_irq; int /*<<< orphan*/  dev; scalar_t__ rx_irq; scalar_t__ irq; int /*<<< orphan*/  reg_cache_size; } ;
struct TYPE_4__ {scalar_t__ has_wakeup; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;int /*<<< orphan*/  (* request ) (scalar_t__) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPCR1 ; 
 int /*<<< orphan*/  SPCR2 ; 
 int /*<<< orphan*/  WAKEUPEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_mcbsp_irq_handler ; 
 int /*<<< orphan*/  omap_mcbsp_rx_irq_handler ; 
 int /*<<< orphan*/  omap_mcbsp_tx_irq_handler ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 

__attribute__((used)) static int omap_mcbsp_request(struct omap_mcbsp *mcbsp)
{
	void *reg_cache;
	int err;

	reg_cache = kzalloc(mcbsp->reg_cache_size, GFP_KERNEL);
	if (!reg_cache)
		return -ENOMEM;

	spin_lock(&mcbsp->lock);
	if (!mcbsp->free) {
		dev_err(mcbsp->dev, "McBSP%d is currently in use\n", mcbsp->id);
		err = -EBUSY;
		goto err_kfree;
	}

	mcbsp->free = false;
	mcbsp->reg_cache = reg_cache;
	spin_unlock(&mcbsp->lock);

	if(mcbsp->pdata->ops && mcbsp->pdata->ops->request)
		mcbsp->pdata->ops->request(mcbsp->id - 1);

	/*
	 * Make sure that transmitter, receiver and sample-rate generator are
	 * not running before activating IRQs.
	 */
	MCBSP_WRITE(mcbsp, SPCR1, 0);
	MCBSP_WRITE(mcbsp, SPCR2, 0);

	if (mcbsp->irq) {
		err = request_irq(mcbsp->irq, omap_mcbsp_irq_handler, 0,
				  "McBSP", (void *)mcbsp);
		if (err != 0) {
			dev_err(mcbsp->dev, "Unable to request IRQ\n");
			goto err_clk_disable;
		}
	} else {
		err = request_irq(mcbsp->tx_irq, omap_mcbsp_tx_irq_handler, 0,
				  "McBSP TX", (void *)mcbsp);
		if (err != 0) {
			dev_err(mcbsp->dev, "Unable to request TX IRQ\n");
			goto err_clk_disable;
		}

		err = request_irq(mcbsp->rx_irq, omap_mcbsp_rx_irq_handler, 0,
				  "McBSP RX", (void *)mcbsp);
		if (err != 0) {
			dev_err(mcbsp->dev, "Unable to request RX IRQ\n");
			goto err_free_irq;
		}
	}

	return 0;
err_free_irq:
	free_irq(mcbsp->tx_irq, (void *)mcbsp);
err_clk_disable:
	if(mcbsp->pdata->ops && mcbsp->pdata->ops->free)
		mcbsp->pdata->ops->free(mcbsp->id - 1);

	/* Disable wakeup behavior */
	if (mcbsp->pdata->has_wakeup)
		MCBSP_WRITE(mcbsp, WAKEUPEN, 0);

	spin_lock(&mcbsp->lock);
	mcbsp->free = true;
	mcbsp->reg_cache = NULL;
err_kfree:
	spin_unlock(&mcbsp->lock);
	kfree(reg_cache);

	return err;
}