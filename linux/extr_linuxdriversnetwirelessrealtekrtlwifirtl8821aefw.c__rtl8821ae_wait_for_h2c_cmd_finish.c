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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HMETFR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl8821ae_wait_for_h2c_cmd_finish(struct rtl_priv *rtlpriv)
{
	u8 val;
	u16 count = 0;

	do {
		val = rtl_read_byte(rtlpriv, REG_HMETFR);
		mdelay(1);
		count++;
	} while ((val & 0x0F) && (count < 1000));
}