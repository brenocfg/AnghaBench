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
struct config_item {int dummy; } ;
struct cfs_overlay_item {char* path; size_t dtbo_size; scalar_t__ ov_id; int /*<<< orphan*/ * dtbo; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENOMEM ; 
 size_t EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (void const*,size_t,int /*<<< orphan*/ ) ; 
 int of_overlay_fdt_apply (int /*<<< orphan*/ *,size_t,scalar_t__*) ; 
 struct cfs_overlay_item* to_cfs_overlay_item (struct config_item*) ; 

ssize_t cfs_overlay_item_dtbo_write(struct config_item *item,
		const void *buf, size_t count)
{
	struct cfs_overlay_item *overlay = to_cfs_overlay_item(item);
	int err;

	/* if it's set do not allow changes */
	if (overlay->path[0] != '\0' || overlay->dtbo_size > 0)
		return -EPERM;

	/* copy the contents */
	overlay->dtbo = kmemdup(buf, count, GFP_KERNEL);
	if (overlay->dtbo == NULL)
		return -ENOMEM;

	overlay->dtbo_size = count;

	err = of_overlay_fdt_apply(overlay->dtbo, overlay->dtbo_size,
				   &overlay->ov_id);
	if (err != 0)
		goto out_err;

	return count;

out_err:
	kfree(overlay->dtbo);
	overlay->dtbo = NULL;
	overlay->dtbo_size = 0;
	overlay->ov_id = 0;

	return err;
}