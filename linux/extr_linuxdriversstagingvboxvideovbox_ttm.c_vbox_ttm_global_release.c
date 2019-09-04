#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem_global_ref; TYPE_1__ bo_global_ref; } ;
struct vbox_private {TYPE_2__ ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_global_item_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vbox_ttm_global_release(struct vbox_private *vbox)
{
	drm_global_item_unref(&vbox->ttm.bo_global_ref.ref);
	drm_global_item_unref(&vbox->ttm.mem_global_ref);
}