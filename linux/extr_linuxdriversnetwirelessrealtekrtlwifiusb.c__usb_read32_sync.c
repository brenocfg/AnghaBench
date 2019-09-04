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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _usb_read_sync (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 _usb_read32_sync(struct rtl_priv *rtlpriv, u32 addr)
{
	return _usb_read_sync(rtlpriv, addr, 4);
}