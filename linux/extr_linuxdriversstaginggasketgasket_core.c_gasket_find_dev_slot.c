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
struct gasket_internal_desc {int /*<<< orphan*/  mutex; TYPE_1__** devs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int GASKET_DEV_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int gasket_find_dev_slot(struct gasket_internal_desc *internal_desc,
				const char *kobj_name)
{
	int i;

	mutex_lock(&internal_desc->mutex);

	/* Search for a previous instance of this device. */
	for (i = 0; i < GASKET_DEV_MAX; i++) {
		if (internal_desc->devs[i] &&
		    strcmp(internal_desc->devs[i]->kobj_name, kobj_name) == 0) {
			pr_err("Duplicate device %s\n", kobj_name);
			mutex_unlock(&internal_desc->mutex);
			return -EBUSY;
		}
	}

	/* Find a free device slot. */
	for (i = 0; i < GASKET_DEV_MAX; i++) {
		if (!internal_desc->devs[i])
			break;
	}

	if (i == GASKET_DEV_MAX) {
		pr_err("Too many registered devices; max %d\n", GASKET_DEV_MAX);
		mutex_unlock(&internal_desc->mutex);
		return -EBUSY;
	}

	mutex_unlock(&internal_desc->mutex);
	return i;
}