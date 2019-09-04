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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RSCTRL_RESET_MASK ; 
 scalar_t__ RSCTRL_RG ; 
 int /*<<< orphan*/  pllctrl_regs ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsctrl_enable_rspll_write () ; 
 scalar_t__ rspll_offset ; 

__attribute__((used)) static int rsctrl_restart_handler(struct notifier_block *this,
				  unsigned long mode, void *cmd)
{
	/* enable write access to RSTCTRL */
	rsctrl_enable_rspll_write();

	/* reset the SOC */
	regmap_update_bits(pllctrl_regs, rspll_offset + RSCTRL_RG,
			   RSCTRL_RESET_MASK, 0);

	return NOTIFY_DONE;
}