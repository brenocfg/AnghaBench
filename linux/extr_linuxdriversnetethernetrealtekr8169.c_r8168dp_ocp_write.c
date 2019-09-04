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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCPAR ; 
 int OCPAR_FLAG ; 
 int /*<<< orphan*/  OCPDR ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_ocpar_cond ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void r8168dp_ocp_write(struct rtl8169_private *tp, u8 mask, u16 reg,
			      u32 data)
{
	RTL_W32(tp, OCPDR, data);
	RTL_W32(tp, OCPAR, OCPAR_FLAG | ((u32)mask & 0x0f) << 12 | (reg & 0x0fff));
	rtl_udelay_loop_wait_low(tp, &rtl_ocpar_cond, 100, 20);
}