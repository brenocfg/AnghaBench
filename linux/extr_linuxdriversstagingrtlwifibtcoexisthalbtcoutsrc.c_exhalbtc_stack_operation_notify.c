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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cnt_stack_operation_notify; } ;
struct btc_coexist {TYPE_1__ statistics; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 

void exhalbtc_stack_operation_notify(struct btc_coexist *btcoexist, u8 type)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_stack_operation_notify++;
}