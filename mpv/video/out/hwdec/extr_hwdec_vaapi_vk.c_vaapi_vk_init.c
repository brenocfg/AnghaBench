#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {int /*<<< orphan*/  ra; struct priv_owner* priv; } ;
struct priv_owner {int /*<<< orphan*/  interop_unmap; int /*<<< orphan*/  interop_map; } ;
struct TYPE_2__ {int tex; } ;
struct pl_gpu {TYPE_1__ import_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec const*,char*) ; 
 int PL_HANDLE_DMA_BUF ; 
 struct pl_gpu* ra_pl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaapi_vk_map ; 
 int /*<<< orphan*/  vaapi_vk_unmap ; 

bool vaapi_vk_init(const struct ra_hwdec *hw)
{
   struct priv_owner *p = hw->priv;

    const struct pl_gpu *gpu = ra_pl_get(hw->ra);
    if (!gpu) {
        // This is not a Vulkan RA;
        return false;
    }

    if (!(gpu->import_caps.tex & PL_HANDLE_DMA_BUF)) {
        MP_VERBOSE(hw, "VAAPI Vulkan interop requires support for "
                        "dma_buf import in Vulkan.\n");
        return false;
    }

    MP_VERBOSE(hw, "using VAAPI Vulkan interop\n");

    p->interop_map = vaapi_vk_map;
    p->interop_unmap = vaapi_vk_unmap;

    return true;
}