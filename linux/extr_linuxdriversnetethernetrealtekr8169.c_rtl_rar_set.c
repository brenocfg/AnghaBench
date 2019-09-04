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
struct rtl8169_private {scalar_t__ mac_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cfg9346 ; 
 int /*<<< orphan*/  Cfg9346_Lock ; 
 int /*<<< orphan*/  Cfg9346_Unlock ; 
 int /*<<< orphan*/  MAC0 ; 
 int /*<<< orphan*/  MAC4 ; 
 scalar_t__ RTL_GIGA_MAC_VER_34 ; 
 int /*<<< orphan*/  RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_rar_exgmac_set (struct rtl8169_private*,int*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_rar_set(struct rtl8169_private *tp, u8 *addr)
{
	rtl_lock_work(tp);

	RTL_W8(tp, Cfg9346, Cfg9346_Unlock);

	RTL_W32(tp, MAC4, addr[4] | addr[5] << 8);
	RTL_R32(tp, MAC4);

	RTL_W32(tp, MAC0, addr[0] | addr[1] << 8 | addr[2] << 16 | addr[3] << 24);
	RTL_R32(tp, MAC0);

	if (tp->mac_version == RTL_GIGA_MAC_VER_34)
		rtl_rar_exgmac_set(tp, addr);

	RTL_W8(tp, Cfg9346, Cfg9346_Lock);

	rtl_unlock_work(tp);
}