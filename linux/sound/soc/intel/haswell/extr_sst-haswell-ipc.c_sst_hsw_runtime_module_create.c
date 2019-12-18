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
struct sst_module_runtime {int /*<<< orphan*/  id; } ;
struct sst_module {int dummy; } ;
struct sst_hsw {struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct sst_module* sst_module_get_from_id (struct sst_dsp*,int) ; 
 int sst_module_runtime_alloc_blocks (struct sst_module_runtime*,int) ; 
 int /*<<< orphan*/  sst_module_runtime_free (struct sst_module_runtime*) ; 
 struct sst_module_runtime* sst_module_runtime_new (struct sst_module*,int,int /*<<< orphan*/ *) ; 

struct sst_module_runtime *sst_hsw_runtime_module_create(struct sst_hsw *hsw,
	int mod_id, int offset)
{
	struct sst_dsp *dsp = hsw->dsp;
	struct sst_module *module;
	struct sst_module_runtime *runtime;
	int err;

	module = sst_module_get_from_id(dsp, mod_id);
	if (module == NULL) {
		dev_err(dsp->dev, "error: failed to get module %d for pcm\n",
			mod_id);
		return NULL;
	}

	runtime = sst_module_runtime_new(module, mod_id, NULL);
	if (runtime == NULL) {
		dev_err(dsp->dev, "error: failed to create module %d runtime\n",
			mod_id);
		return NULL;
	}

	err = sst_module_runtime_alloc_blocks(runtime, offset);
	if (err < 0) {
		dev_err(dsp->dev, "error: failed to alloc blocks for module %d runtime\n",
			mod_id);
		sst_module_runtime_free(runtime);
		return NULL;
	}

	dev_dbg(dsp->dev, "runtime id %d created for module %d\n", runtime->id,
		mod_id);
	return runtime;
}