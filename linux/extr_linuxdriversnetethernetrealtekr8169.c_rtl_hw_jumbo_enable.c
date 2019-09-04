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
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct rtl8169_private*) ;} ;
struct rtl8169_private {TYPE_1__ jumbo_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cfg9346 ; 
 int /*<<< orphan*/  Cfg9346_Lock ; 
 int /*<<< orphan*/  Cfg9346_Unlock ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_jumbo_enable(struct rtl8169_private *tp)
{
	if (tp->jumbo_ops.enable) {
		RTL_W8(tp, Cfg9346, Cfg9346_Unlock);
		tp->jumbo_ops.enable(tp);
		RTL_W8(tp, Cfg9346, Cfg9346_Lock);
	}
}