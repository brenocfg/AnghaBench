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
struct ohci_at91_priv {int clocked; int /*<<< orphan*/  fclk; int /*<<< orphan*/  iclk; int /*<<< orphan*/  hclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91_start_clock(struct ohci_at91_priv *ohci_at91)
{
	if (ohci_at91->clocked)
		return;

	clk_set_rate(ohci_at91->fclk, 48000000);
	clk_prepare_enable(ohci_at91->hclk);
	clk_prepare_enable(ohci_at91->iclk);
	clk_prepare_enable(ohci_at91->fclk);
	ohci_at91->clocked = true;
}