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
struct sst_module_template {int /*<<< orphan*/  entry; int /*<<< orphan*/  persistent_size; int /*<<< orphan*/  scratch_size; int /*<<< orphan*/  id; } ;
struct sst_module {int /*<<< orphan*/  list; int /*<<< orphan*/  runtime_list; int /*<<< orphan*/  block_list; int /*<<< orphan*/  state; int /*<<< orphan*/  entry; int /*<<< orphan*/  persistent_size; int /*<<< orphan*/  scratch_size; struct sst_fw* sst_fw; struct sst_dsp* dsp; int /*<<< orphan*/  id; } ;
struct sst_fw {struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  module_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SST_MODULE_STATE_UNLOADED ; 
 struct sst_module* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct sst_module *sst_module_new(struct sst_fw *sst_fw,
	struct sst_module_template *template, void *private)
{
	struct sst_dsp *dsp = sst_fw->dsp;
	struct sst_module *sst_module;

	sst_module = kzalloc(sizeof(*sst_module), GFP_KERNEL);
	if (sst_module == NULL)
		return NULL;

	sst_module->id = template->id;
	sst_module->dsp = dsp;
	sst_module->sst_fw = sst_fw;
	sst_module->scratch_size = template->scratch_size;
	sst_module->persistent_size = template->persistent_size;
	sst_module->entry = template->entry;
	sst_module->state = SST_MODULE_STATE_UNLOADED;

	INIT_LIST_HEAD(&sst_module->block_list);
	INIT_LIST_HEAD(&sst_module->runtime_list);

	mutex_lock(&dsp->mutex);
	list_add(&sst_module->list, &dsp->module_list);
	mutex_unlock(&dsp->mutex);

	return sst_module;
}