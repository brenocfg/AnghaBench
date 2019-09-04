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
typedef  int /*<<< orphan*/  u32 ;
struct udc {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_ADDBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_DEVCFG_SPD ; 
 int /*<<< orphan*/  UDC_DEVCFG_SPD_FS ; 
 int /*<<< orphan*/  UDC_DEVCFG_SPD_HS ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_basic_init (struct udc*) ; 
 int /*<<< orphan*/  udc_mask_unused_interrupts (struct udc*) ; 
 int /*<<< orphan*/  udc_setup_endpoints (struct udc*) ; 
 int /*<<< orphan*/  udc_soft_reset (struct udc*) ; 
 scalar_t__ use_fullspeed ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int startup_registers(struct udc *dev)
{
	u32 tmp;

	/* init controller by soft reset */
	udc_soft_reset(dev);

	/* mask not needed interrupts */
	udc_mask_unused_interrupts(dev);

	/* put into initial config */
	udc_basic_init(dev);
	/* link up all endpoints */
	udc_setup_endpoints(dev);

	/* program speed */
	tmp = readl(&dev->regs->cfg);
	if (use_fullspeed)
		tmp = AMD_ADDBITS(tmp, UDC_DEVCFG_SPD_FS, UDC_DEVCFG_SPD);
	else
		tmp = AMD_ADDBITS(tmp, UDC_DEVCFG_SPD_HS, UDC_DEVCFG_SPD);
	writel(tmp, &dev->regs->cfg);

	return 0;
}