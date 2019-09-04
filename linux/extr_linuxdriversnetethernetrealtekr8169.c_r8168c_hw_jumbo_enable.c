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
 int /*<<< orphan*/  Config3 ; 
 int /*<<< orphan*/  Config4 ; 
 int Jumbo_En0 ; 
 int Jumbo_En1 ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ_512B ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8168c_hw_jumbo_enable(struct rtl8169_private *tp)
{
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) | Jumbo_En0);
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) | Jumbo_En1);
	rtl_tx_performance_tweak(tp, PCI_EXP_DEVCTL_READRQ_512B);
}