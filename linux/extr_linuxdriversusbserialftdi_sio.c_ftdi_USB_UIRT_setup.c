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
struct ftdi_private {int custom_divisor; int force_baud; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_SPD_CUST ; 

__attribute__((used)) static void ftdi_USB_UIRT_setup(struct ftdi_private *priv)
{
	priv->flags |= ASYNC_SPD_CUST;
	priv->custom_divisor = 77;
	priv->force_baud = 38400;
}