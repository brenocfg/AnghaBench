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
struct r8152 {int version; } ;

/* Variables and functions */
#define  RTL_VER_03 131 
#define  RTL_VER_04 130 
#define  RTL_VER_05 129 
#define  RTL_VER_06 128 
 int /*<<< orphan*/  r8153_mac_clk_spd (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u1u2en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_runtime_suspend_enable (struct r8152*,int) ; 

__attribute__((used)) static void rtl8153_runtime_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		r8153_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		r8153_mac_clk_spd(tp, true);
		rtl_runtime_suspend_enable(tp, true);
	} else {
		rtl_runtime_suspend_enable(tp, false);
		r8153_mac_clk_spd(tp, false);

		switch (tp->version) {
		case RTL_VER_03:
		case RTL_VER_04:
			break;
		case RTL_VER_05:
		case RTL_VER_06:
		default:
			r8153_u2p3en(tp, true);
			break;
		}

		r8153_u1u2en(tp, true);
	}
}