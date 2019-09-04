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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct iwl_mvm {int init_status; TYPE_1__ led; } ;

/* Variables and functions */
 int IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

void iwl_mvm_leds_exit(struct iwl_mvm *mvm)
{
	if (!(mvm->init_status & IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE))
		return;

	led_classdev_unregister(&mvm->led);
	kfree(mvm->led.name);
	mvm->init_status &= ~IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE;
}