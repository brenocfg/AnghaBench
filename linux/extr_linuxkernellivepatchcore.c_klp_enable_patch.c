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
struct klp_patch {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __klp_enable_patch (struct klp_patch*) ; 
 int /*<<< orphan*/  klp_is_patch_registered (struct klp_patch*) ; 
 int /*<<< orphan*/  klp_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int klp_enable_patch(struct klp_patch *patch)
{
	int ret;

	mutex_lock(&klp_mutex);

	if (!klp_is_patch_registered(patch)) {
		ret = -EINVAL;
		goto err;
	}

	ret = __klp_enable_patch(patch);

err:
	mutex_unlock(&klp_mutex);
	return ret;
}