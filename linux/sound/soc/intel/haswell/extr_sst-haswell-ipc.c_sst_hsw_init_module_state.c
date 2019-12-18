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
struct sst_module {int /*<<< orphan*/  state; } ;
struct sst_hsw {int /*<<< orphan*/  dsp; } ;
typedef  enum sst_hsw_module_id { ____Placeholder_sst_hsw_module_id } sst_hsw_module_id ;

/* Variables and functions */
 int SST_HSW_MAX_MODULE_ID ; 
 int SST_HSW_MODULE_BASE_FW ; 
 int SST_HSW_MODULE_WAVES ; 
 int /*<<< orphan*/  SST_MODULE_STATE_ACTIVE ; 
 int /*<<< orphan*/  SST_MODULE_STATE_INITIALIZED ; 
 struct sst_module* sst_module_get_from_id (int /*<<< orphan*/ ,int) ; 

void sst_hsw_init_module_state(struct sst_hsw *hsw)
{
	struct sst_module *module;
	enum sst_hsw_module_id id;

	/* the base fw contains several modules */
	for (id = SST_HSW_MODULE_BASE_FW; id < SST_HSW_MAX_MODULE_ID; id++) {
		module = sst_module_get_from_id(hsw->dsp, id);
		if (module) {
			/* module waves is active only after being enabled */
			if (id == SST_HSW_MODULE_WAVES)
				module->state = SST_MODULE_STATE_INITIALIZED;
			else
				module->state = SST_MODULE_STATE_ACTIVE;
		}
	}
}