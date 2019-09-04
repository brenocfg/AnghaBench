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
struct gasket_internal_desc {struct gasket_driver_desc const* driver_desc; int /*<<< orphan*/  class; } ;
struct gasket_driver_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  GASKET_DEV_MAX ; 
 int GASKET_FRAMEWORK_DESC_MAX ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 struct gasket_internal_desc* g_descs ; 
 int /*<<< orphan*/  g_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gasket_unregister_device(const struct gasket_driver_desc *driver_desc)
{
	int i, desc_idx;
	struct gasket_internal_desc *internal_desc = NULL;

	mutex_lock(&g_mutex);
	for (i = 0; i < GASKET_FRAMEWORK_DESC_MAX; i++) {
		if (g_descs[i].driver_desc == driver_desc) {
			internal_desc = &g_descs[i];
			desc_idx = i;
			break;
		}
	}

	if (!internal_desc) {
		mutex_unlock(&g_mutex);
		pr_err("request to unregister unknown desc: %s, %d:%d\n",
		       driver_desc->name, driver_desc->major,
		       driver_desc->minor);
		return;
	}

	unregister_chrdev_region(MKDEV(driver_desc->major, driver_desc->minor),
				 GASKET_DEV_MAX);

	class_destroy(internal_desc->class);

	/* Finally, effectively "remove" the driver. */
	g_descs[desc_idx].driver_desc = NULL;
	mutex_unlock(&g_mutex);

	pr_debug("removed %s driver\n", driver_desc->name);
}