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
typedef  int /*<<< orphan*/  u32 ;
struct sst_module {scalar_t__ state; } ;
struct sst_hsw {int /*<<< orphan*/  dsp; } ;

/* Variables and functions */
 scalar_t__ SST_MODULE_STATE_ACTIVE ; 
 struct sst_module* sst_module_get_from_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool sst_hsw_is_module_active(struct sst_hsw *hsw, u32 module_id)
{
	struct sst_module *module;

	module = sst_module_get_from_id(hsw->dsp, module_id);
	if (module != NULL && module->state == SST_MODULE_STATE_ACTIVE)
		return true;
	else
		return false;
}