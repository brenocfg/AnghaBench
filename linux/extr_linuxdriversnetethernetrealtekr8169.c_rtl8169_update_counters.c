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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChipCmd ; 
 int CmdRxEnb ; 
 int /*<<< orphan*/  CounterDump ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int rtl8169_do_counters (struct rtl8169_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtl8169_update_counters(struct rtl8169_private *tp)
{
	u8 val = RTL_R8(tp, ChipCmd);

	/*
	 * Some chips are unable to dump tally counters when the receiver
	 * is disabled. If 0xff chip may be in a PCI power-save state.
	 */
	if (!(val & CmdRxEnb) || val == 0xff)
		return true;

	return rtl8169_do_counters(tp, CounterDump);
}