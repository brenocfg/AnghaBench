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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct vbox_private {TYPE_1__ ttm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bdev; } ;
struct vbox_bo {int /*<<< orphan*/  placement; TYPE_2__ bo; int /*<<< orphan*/  gem; } ;
struct drm_device {struct vbox_private* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_VRAM ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct vbox_bo*) ; 
 struct vbox_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,int,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int /*<<< orphan*/  vbox_bo_ttm_destroy ; 
 int /*<<< orphan*/  vbox_ttm_placement (struct vbox_bo*,int) ; 

int vbox_bo_create(struct drm_device *dev, int size, int align,
		   u32 flags, struct vbox_bo **pvboxbo)
{
	struct vbox_private *vbox = dev->dev_private;
	struct vbox_bo *vboxbo;
	size_t acc_size;
	int ret;

	vboxbo = kzalloc(sizeof(*vboxbo), GFP_KERNEL);
	if (!vboxbo)
		return -ENOMEM;

	ret = drm_gem_object_init(dev, &vboxbo->gem, size);
	if (ret)
		goto err_free_vboxbo;

	vboxbo->bo.bdev = &vbox->ttm.bdev;

	vbox_ttm_placement(vboxbo, TTM_PL_FLAG_VRAM | TTM_PL_FLAG_SYSTEM);

	acc_size = ttm_bo_dma_acc_size(&vbox->ttm.bdev, size,
				       sizeof(struct vbox_bo));

	ret = ttm_bo_init(&vbox->ttm.bdev, &vboxbo->bo, size,
			  ttm_bo_type_device, &vboxbo->placement,
			  align >> PAGE_SHIFT, false, acc_size,
			  NULL, NULL, vbox_bo_ttm_destroy);
	if (ret)
		goto err_free_vboxbo;

	*pvboxbo = vboxbo;

	return 0;

err_free_vboxbo:
	kfree(vboxbo);
	return ret;
}