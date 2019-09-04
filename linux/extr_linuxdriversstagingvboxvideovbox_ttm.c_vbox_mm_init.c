#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttm_bo_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  object; } ;
struct TYPE_6__ {TYPE_1__ ref; } ;
struct TYPE_8__ {struct ttm_bo_device bdev; TYPE_2__ bo_global_ref; } ;
struct vbox_private {int available_vram_size; TYPE_4__ ttm; int /*<<< orphan*/  fb_mtrr; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  pdev; TYPE_3__* anon_inode; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_device_init (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_device_release (struct ttm_bo_device*) ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbox_bo_driver ; 
 int vbox_ttm_global_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_ttm_global_release (struct vbox_private*) ; 

int vbox_mm_init(struct vbox_private *vbox)
{
	int ret;
	struct drm_device *dev = vbox->dev;
	struct ttm_bo_device *bdev = &vbox->ttm.bdev;

	ret = vbox_ttm_global_init(vbox);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&vbox->ttm.bdev,
				 vbox->ttm.bo_global_ref.ref.object,
				 &vbox_bo_driver,
				 dev->anon_inode->i_mapping,
				 DRM_FILE_PAGE_OFFSET, true);
	if (ret) {
		DRM_ERROR("Error initialising bo driver; %d\n", ret);
		goto err_ttm_global_release;
	}

	ret = ttm_bo_init_mm(bdev, TTM_PL_VRAM,
			     vbox->available_vram_size >> PAGE_SHIFT);
	if (ret) {
		DRM_ERROR("Failed ttm VRAM init: %d\n", ret);
		goto err_device_release;
	}

#ifdef DRM_MTRR_WC
	vbox->fb_mtrr = drm_mtrr_add(pci_resource_start(dev->pdev, 0),
				     pci_resource_len(dev->pdev, 0),
				     DRM_MTRR_WC);
#else
	vbox->fb_mtrr = arch_phys_wc_add(pci_resource_start(dev->pdev, 0),
					 pci_resource_len(dev->pdev, 0));
#endif
	return 0;

err_device_release:
	ttm_bo_device_release(&vbox->ttm.bdev);
err_ttm_global_release:
	vbox_ttm_global_release(vbox);
	return ret;
}