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
struct vbox_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct vbox_bo* gem_to_vbox_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vbox_bo_unref (struct vbox_bo**) ; 

void vbox_gem_free_object(struct drm_gem_object *obj)
{
	struct vbox_bo *vbox_bo = gem_to_vbox_bo(obj);

	vbox_bo_unref(&vbox_bo);
}