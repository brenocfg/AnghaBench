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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 _halmac_reg_read_8(void *p, u32 offset)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p;

	return rtl_read_byte(rtlpriv, offset);
}