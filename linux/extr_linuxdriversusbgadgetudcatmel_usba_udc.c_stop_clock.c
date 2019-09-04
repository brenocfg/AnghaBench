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
struct usba_udc {int clocked; int /*<<< orphan*/  pclk; int /*<<< orphan*/  hclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_clock(struct usba_udc *udc)
{
	if (!udc->clocked)
		return;

	clk_disable_unprepare(udc->hclk);
	clk_disable_unprepare(udc->pclk);

	udc->clocked = false;
}