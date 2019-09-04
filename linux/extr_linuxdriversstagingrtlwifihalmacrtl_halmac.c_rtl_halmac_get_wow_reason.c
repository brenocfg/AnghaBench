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
 int rtl_read_byte (struct rtl_priv*,int) ; 

int rtl_halmac_get_wow_reason(struct rtl_priv *rtlpriv, u8 *reason)
{
	u8 val8;
	int err = -1;

	val8 = rtl_read_byte(rtlpriv, 0x1C7);
	if (val8 == 0xEA)
		goto out;

	*reason = val8;
	err = 0;
out:
	return err;
}