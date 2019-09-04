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
struct usbnet {TYPE_1__* intf; } ;
struct TYPE_2__ {int needs_remote_wakeup; } ;

/* Variables and functions */

__attribute__((used)) static int smsc75xx_manage_power(struct usbnet *dev, int on)
{
	dev->intf->needs_remote_wakeup = on;
	return 0;
}