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
struct TYPE_4__ {int num_placement; } ;
struct vbox_bo {TYPE_2__ placement; int /*<<< orphan*/  bo; TYPE_1__* placements; scalar_t__ pin_count; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,struct vbox_bo*) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,TYPE_2__*,struct ttm_operation_ctx*) ; 

int vbox_bo_unpin(struct vbox_bo *bo)
{
	struct ttm_operation_ctx ctx = { false, false };
	int i, ret;

	if (!bo->pin_count) {
		DRM_ERROR("unpin bad %p\n", bo);
		return 0;
	}
	bo->pin_count--;
	if (bo->pin_count)
		return 0;

	for (i = 0; i < bo->placement.num_placement; i++)
		bo->placements[i].flags &= ~TTM_PL_FLAG_NO_EVICT;

	ret = ttm_bo_validate(&bo->bo, &bo->placement, &ctx);
	if (ret)
		return ret;

	return 0;
}