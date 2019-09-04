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
struct adapter {int dummy; } ;

/* Variables and functions */

void rtw_free_pwrctrl_priv(struct adapter *adapter)
{
#ifdef CONFIG_PNO_SUPPORT
	if (pwrctrlpriv->pnlo_info != NULL)
		printk("****** pnlo_info memory leak********\n");

	if (pwrctrlpriv->pscan_info != NULL)
		printk("****** pscan_info memory leak********\n");

	if (pwrctrlpriv->pno_ssid_list != NULL)
		printk("****** pno_ssid_list memory leak********\n");
#endif
}