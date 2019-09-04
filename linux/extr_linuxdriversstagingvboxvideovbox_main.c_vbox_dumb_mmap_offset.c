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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vbox_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put (struct drm_gem_object*) ; 
 struct vbox_bo* gem_to_vbox_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbox_bo_mmap_offset (struct vbox_bo*) ; 

int
vbox_dumb_mmap_offset(struct drm_file *file,
		      struct drm_device *dev,
		      u32 handle, u64 *offset)
{
	struct drm_gem_object *obj;
	int ret;
	struct vbox_bo *bo;

	mutex_lock(&dev->struct_mutex);
	obj = drm_gem_object_lookup(file, handle);
	if (!obj) {
		ret = -ENOENT;
		goto out_unlock;
	}

	bo = gem_to_vbox_bo(obj);
	*offset = vbox_bo_mmap_offset(bo);

	drm_gem_object_put(obj);
	ret = 0;

out_unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}