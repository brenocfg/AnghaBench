#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtl8169_private {int /*<<< orphan*/  cp_cmd; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int Beacon_en ; 
 int /*<<< orphan*/  CPCMD_QUIRK_MASK ; 
 int /*<<< orphan*/  CPlusCmd ; 
 int /*<<< orphan*/  Config3 ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ_4096B ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_hw_start_8168cp_2(struct rtl8169_private *tp)
{
	rtl_set_def_aspm_entry_latency(tp);

	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(tp, PCI_EXP_DEVCTL_READRQ_4096B);

	tp->cp_cmd &= CPCMD_QUIRK_MASK;
	RTL_W16(tp, CPlusCmd, tp->cp_cmd);
}