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
struct itco_wdt_platform_data {struct iTCO_wdt_private* no_reboot_priv; scalar_t__ update_no_reboot_bit; } ;
struct iTCO_wdt_private {int iTCO_version; struct iTCO_wdt_private* no_reboot_priv; scalar_t__ update_no_reboot_bit; } ;

/* Variables and functions */
 scalar_t__ update_no_reboot_bit_def ; 
 scalar_t__ update_no_reboot_bit_mem ; 
 scalar_t__ update_no_reboot_bit_pci ; 

__attribute__((used)) static void iTCO_wdt_no_reboot_bit_setup(struct iTCO_wdt_private *p,
		struct itco_wdt_platform_data *pdata)
{
	if (pdata->update_no_reboot_bit) {
		p->update_no_reboot_bit = pdata->update_no_reboot_bit;
		p->no_reboot_priv = pdata->no_reboot_priv;
		return;
	}

	if (p->iTCO_version >= 2)
		p->update_no_reboot_bit = update_no_reboot_bit_mem;
	else if (p->iTCO_version == 1)
		p->update_no_reboot_bit = update_no_reboot_bit_pci;
	else
		p->update_no_reboot_bit = update_no_reboot_bit_def;

	p->no_reboot_priv = p;
}