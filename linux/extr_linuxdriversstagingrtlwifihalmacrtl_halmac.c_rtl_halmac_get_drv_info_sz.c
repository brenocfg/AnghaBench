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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */

int rtl_halmac_get_drv_info_sz(struct rtl_priv *rtlpriv, u8 *sz)
{
	/*	enum halmac_ret_status status; */
	u8 dw = 6; /* max number */

	*sz = dw * 8;
	return 0;
}