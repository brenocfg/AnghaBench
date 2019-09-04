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
struct TYPE_2__ {scalar_t__ fwsize; int /*<<< orphan*/  pfirmware; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;

/* Variables and functions */
 int _halmac_init_hal (struct rtl_priv*,int /*<<< orphan*/ ,scalar_t__) ; 

int rtl_halmac_init_hal(struct rtl_priv *rtlpriv)
{
	if (!rtlpriv->rtlhal.pfirmware || rtlpriv->rtlhal.fwsize == 0)
		return -1;

	return _halmac_init_hal(rtlpriv, rtlpriv->rtlhal.pfirmware,
				rtlpriv->rtlhal.fwsize);
}