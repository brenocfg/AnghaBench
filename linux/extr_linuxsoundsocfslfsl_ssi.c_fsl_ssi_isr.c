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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct fsl_ssi {int /*<<< orphan*/  dbg_stats; TYPE_1__* soc; struct regmap* regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int sisr_write_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_SSI_SISR ; 
 int /*<<< orphan*/  fsl_ssi_dbg_isr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t fsl_ssi_isr(int irq, void *dev_id)
{
	struct fsl_ssi *ssi = dev_id;
	struct regmap *regs = ssi->regs;
	u32 sisr, sisr2;

	regmap_read(regs, REG_SSI_SISR, &sisr);

	sisr2 = sisr & ssi->soc->sisr_write_mask;
	/* Clear the bits that we set */
	if (sisr2)
		regmap_write(regs, REG_SSI_SISR, sisr2);

	fsl_ssi_dbg_isr(&ssi->dbg_stats, sisr);

	return IRQ_HANDLED;
}