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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int RX_CONFIG_ACCEPT_MASK ; 
 int /*<<< orphan*/  RxConfig ; 

__attribute__((used)) static void rtl_rx_close(struct rtl8169_private *tp)
{
	RTL_W32(tp, RxConfig, RTL_R32(tp, RxConfig) & ~RX_CONFIG_ACCEPT_MASK);
}