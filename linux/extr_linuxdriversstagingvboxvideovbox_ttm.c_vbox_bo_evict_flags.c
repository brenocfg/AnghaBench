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
struct ttm_placement {int dummy; } ;
struct vbox_bo {struct ttm_placement placement; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 struct vbox_bo* vbox_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  vbox_ttm_bo_is_vbox_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  vbox_ttm_placement (struct vbox_bo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vbox_bo_evict_flags(struct ttm_buffer_object *bo, struct ttm_placement *pl)
{
	struct vbox_bo *vboxbo = vbox_bo(bo);

	if (!vbox_ttm_bo_is_vbox_bo(bo))
		return;

	vbox_ttm_placement(vboxbo, TTM_PL_FLAG_SYSTEM);
	*pl = vboxbo->placement;
}