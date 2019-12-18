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
typedef  int u32 ;
struct spdif_dev_data {int rx_chsts_updated; int /*<<< orphan*/  chsts_q; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int XSPDIF_CH_STS_MASK ; 
 scalar_t__ XSPDIF_IRQ_ENABLE_REG ; 
 scalar_t__ XSPDIF_IRQ_STS_REG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t xlnx_spdifrx_irq_handler(int irq, void *arg)
{
	u32 val;
	struct spdif_dev_data *ctx = arg;

	val = readl(ctx->base + XSPDIF_IRQ_STS_REG);
	if (val & XSPDIF_CH_STS_MASK) {
		writel(val & XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IRQ_STS_REG);
		val = readl(ctx->base +
			    XSPDIF_IRQ_ENABLE_REG);
		writel(val & ~XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IRQ_ENABLE_REG);

		ctx->rx_chsts_updated = true;
		wake_up_interruptible(&ctx->chsts_q);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}