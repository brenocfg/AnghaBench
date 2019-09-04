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
 int PCI_EXP_DEVCTL_NOSNOOP_EN ; 
 int PCI_EXP_DEVCTL_READRQ_4096B ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int) ; 

__attribute__((used)) static void r8168b_0_hw_jumbo_disable(struct rtl8169_private *tp)
{
	rtl_tx_performance_tweak(tp,
		PCI_EXP_DEVCTL_READRQ_4096B | PCI_EXP_DEVCTL_NOSNOOP_EN);
}