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
struct nvmem_device {int /*<<< orphan*/  users; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;
struct nvmem_cell {struct nvmem_device* nvmem; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct nvmem_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvmem_cell* nvmem_find_cell (char const*) ; 
 int /*<<< orphan*/  nvmem_mutex ; 
 struct nvmem_device* of_nvmem_find (struct device_node*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nvmem_device *__nvmem_device_get(struct device_node *np,
					       struct nvmem_cell **cellp,
					       const char *cell_id)
{
	struct nvmem_device *nvmem = NULL;

	mutex_lock(&nvmem_mutex);

	if (np) {
		nvmem = of_nvmem_find(np);
		if (!nvmem) {
			mutex_unlock(&nvmem_mutex);
			return ERR_PTR(-EPROBE_DEFER);
		}
	} else {
		struct nvmem_cell *cell = nvmem_find_cell(cell_id);

		if (cell) {
			nvmem = cell->nvmem;
			*cellp = cell;
		}

		if (!nvmem) {
			mutex_unlock(&nvmem_mutex);
			return ERR_PTR(-ENOENT);
		}
	}

	nvmem->users++;
	mutex_unlock(&nvmem_mutex);

	if (!try_module_get(nvmem->owner)) {
		dev_err(&nvmem->dev,
			"could not increase module refcount for cell %s\n",
			nvmem->name);

		mutex_lock(&nvmem_mutex);
		nvmem->users--;
		mutex_unlock(&nvmem_mutex);

		return ERR_PTR(-EINVAL);
	}

	return nvmem;
}