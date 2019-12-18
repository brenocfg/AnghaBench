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

/* Variables and functions */
 int /*<<< orphan*/  SYS_CTRL_CLK_USBHS ; 
 int /*<<< orphan*/  SYS_CTRL_RST_USBHS ; 
 int /*<<< orphan*/  disable_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_block (int /*<<< orphan*/ ,int) ; 

int ehci_hcd_stop(int index)
{
	reset_block(SYS_CTRL_RST_USBHS, 1);
	disable_clock(SYS_CTRL_CLK_USBHS);
	return 0;
}