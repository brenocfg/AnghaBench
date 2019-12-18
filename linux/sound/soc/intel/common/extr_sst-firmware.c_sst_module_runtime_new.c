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
struct sst_module_runtime {int id; int /*<<< orphan*/  list; int /*<<< orphan*/  block_list; struct sst_module* module; struct sst_dsp* dsp; } ;
struct sst_module {int /*<<< orphan*/  runtime_list; struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sst_module_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct sst_module_runtime *sst_module_runtime_new(struct sst_module *module,
	int id, void *private)
{
	struct sst_dsp *dsp = module->dsp;
	struct sst_module_runtime *runtime;

	runtime = kzalloc(sizeof(*runtime), GFP_KERNEL);
	if (runtime == NULL)
		return NULL;

	runtime->id = id;
	runtime->dsp = dsp;
	runtime->module = module;
	INIT_LIST_HEAD(&runtime->block_list);

	mutex_lock(&dsp->mutex);
	list_add(&runtime->list, &module->runtime_list);
	mutex_unlock(&dsp->mutex);

	return runtime;
}