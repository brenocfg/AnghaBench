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
struct r8152 {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int /*<<< orphan*/  r8153_aldps_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_enter_oob (struct r8152*) ; 
 int /*<<< orphan*/  r8153_power_cut_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u1u2en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_drop_queued_tx (struct r8152*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8153_down(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		return;
	}

	r8153_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_power_cut_en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_enter_oob(tp);
	r8153_aldps_en(tp, true);
}