#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_xusb_padctl {TYPE_2__* soc; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* usb3_save_context ) (struct tegra_xusb_padctl*,unsigned int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct tegra_xusb_padctl*,unsigned int) ; 

int tegra_xusb_padctl_usb3_save_context(struct tegra_xusb_padctl *padctl,
					unsigned int port)
{
	if (padctl->soc->ops->usb3_save_context)
		return padctl->soc->ops->usb3_save_context(padctl, port);

	return -ENOSYS;
}