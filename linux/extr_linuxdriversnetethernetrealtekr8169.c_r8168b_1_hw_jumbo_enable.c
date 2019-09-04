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
 int /*<<< orphan*/  Config4 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8168b_0_hw_jumbo_enable (struct rtl8169_private*) ; 

__attribute__((used)) static void r8168b_1_hw_jumbo_enable(struct rtl8169_private *tp)
{
	r8168b_0_hw_jumbo_enable(tp);

	RTL_W8(tp, Config4, RTL_R8(tp, Config4) | (1 << 0));
}