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
struct zd_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zd_usb_reset_rx_idle_timer (struct zd_usb*) ; 

__attribute__((used)) static void zd_usb_reset_rx_idle_timer_tasklet(unsigned long param)
{
	struct zd_usb *usb = (struct zd_usb *)param;

	zd_usb_reset_rx_idle_timer(usb);
}