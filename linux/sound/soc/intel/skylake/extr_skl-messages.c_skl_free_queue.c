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
struct TYPE_2__ {scalar_t__ pvt_id; scalar_t__ instance_id; scalar_t__ module_id; } ;
struct skl_module_pin {int in_use; int /*<<< orphan*/ * tgt_mcfg; int /*<<< orphan*/  pin_state; TYPE_1__ id; scalar_t__ is_dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_PIN_UNBIND ; 

__attribute__((used)) static void skl_free_queue(struct skl_module_pin *mpin, int q_index)
{
	if (mpin[q_index].is_dynamic) {
		mpin[q_index].in_use = false;
		mpin[q_index].id.module_id = 0;
		mpin[q_index].id.instance_id = 0;
		mpin[q_index].id.pvt_id = 0;
	}
	mpin[q_index].pin_state = SKL_PIN_UNBIND;
	mpin[q_index].tgt_mcfg = NULL;
}