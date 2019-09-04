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
struct cfs_overlay_item {scalar_t__ ov_id; struct cfs_overlay_item* dtbo; scalar_t__ fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cfs_overlay_item*) ; 
 int /*<<< orphan*/  of_overlay_remove (scalar_t__*) ; 
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 struct cfs_overlay_item* to_cfs_overlay_item (struct config_item*) ; 

__attribute__((used)) static void cfs_overlay_release(struct config_item *item)
{
	struct cfs_overlay_item *overlay = to_cfs_overlay_item(item);

	if (overlay->ov_id > 0)
		of_overlay_remove(&overlay->ov_id);
	if (overlay->fw)
		release_firmware(overlay->fw);
	/* kfree with NULL is safe */
	kfree(overlay->dtbo);
	kfree(overlay);
}