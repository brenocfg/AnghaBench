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
 int /*<<< orphan*/  rtl8168ep_stop_cmac (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_init_8168g (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_init_8168ep(struct rtl8169_private *tp)
{
	rtl8168ep_stop_cmac(tp);
	rtl_hw_init_8168g(tp);
}