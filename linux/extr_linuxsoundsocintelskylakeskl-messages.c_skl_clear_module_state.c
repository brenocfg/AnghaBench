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
struct skl_module_pin {scalar_t__ pin_state; } ;
struct skl_module_cfg {int /*<<< orphan*/  m_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_MODULE_INIT_DONE ; 
 scalar_t__ SKL_PIN_UNBIND ; 

__attribute__((used)) static void skl_clear_module_state(struct skl_module_pin *mpin, int max,
						struct skl_module_cfg *mcfg)
{
	int i;
	bool found = false;

	for (i = 0; i < max; i++)  {
		if (mpin[i].pin_state == SKL_PIN_UNBIND)
			continue;
		found = true;
		break;
	}

	if (!found)
		mcfg->m_state = SKL_MODULE_INIT_DONE;
	return;
}