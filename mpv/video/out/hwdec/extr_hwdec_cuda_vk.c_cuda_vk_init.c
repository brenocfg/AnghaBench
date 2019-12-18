#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {int /*<<< orphan*/  ra; struct cuda_hw_priv* priv; } ;
struct TYPE_5__ {int tex; int sync; } ;
struct pl_gpu {int /*<<< orphan*/  uuid; TYPE_1__ export_caps; } ;
struct cuda_hw_priv {int handle_type; int /*<<< orphan*/  ext_signal; int /*<<< orphan*/  ext_wait; int /*<<< orphan*/  ext_uninit; int /*<<< orphan*/  ext_init; int /*<<< orphan*/  display_ctx; int /*<<< orphan*/  decode_ctx; TYPE_2__* cu; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cuCtxCreate ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* cuDeviceGetUuid ) (TYPE_3__*,int) ;int /*<<< orphan*/  (* cuDeviceGet ) (int*,int) ;int /*<<< orphan*/  (* cuDeviceGetCount ) (int*) ;int /*<<< orphan*/  cuImportExternalMemory; } ;
typedef  TYPE_2__ CudaFunctions ;
typedef  TYPE_3__ CUuuid ;
typedef  int CUdevice ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_CTX_SCHED_BLOCKING_SYNC ; 
 scalar_t__ IsWindows8OrGreater () ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec const*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec const*,char*,int) ; 
 int /*<<< orphan*/  PL_HANDLE_FD ; 
 int PL_HANDLE_WIN32 ; 
 int PL_HANDLE_WIN32_KMT ; 
 int /*<<< orphan*/  cuda_ext_vk_init ; 
 int /*<<< orphan*/  cuda_ext_vk_signal ; 
 int /*<<< orphan*/  cuda_ext_vk_uninit ; 
 int /*<<< orphan*/  cuda_ext_vk_wait ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pl_gpu* ra_pl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool cuda_vk_init(const struct ra_hwdec *hw) {
    int ret = 0;
    struct cuda_hw_priv *p = hw->priv;
    CudaFunctions *cu = p->cu;

    p->handle_type =
#if HAVE_WIN32_DESKTOP
        IsWindows8OrGreater() ? PL_HANDLE_WIN32 : PL_HANDLE_WIN32_KMT;
#else
        PL_HANDLE_FD;
#endif

    const struct pl_gpu *gpu = ra_pl_get(hw->ra);
    if (gpu != NULL) {
        if (!(gpu->export_caps.tex & p->handle_type)) {
            MP_VERBOSE(hw, "CUDA hwdec with Vulkan requires exportable texture memory of type 0x%X.\n",
                       p->handle_type);
            return false;
        } else if (!(gpu->export_caps.sync & p->handle_type)) {
            MP_VERBOSE(hw, "CUDA hwdec with Vulkan requires exportable semaphores of type 0x%X.\n",
                       p->handle_type);
            return false;
        }
    } else {
        // This is not a Vulkan RA.
        return false;
    }

    if (!cu->cuImportExternalMemory) {
        MP_ERR(hw, "CUDA hwdec with Vulkan requires driver version 410.48 or newer.\n");
        return false;
    }

    int device_count;
    ret = CHECK_CU(cu->cuDeviceGetCount(&device_count));
    if (ret < 0)
        return false;

    CUdevice display_dev = -1;
    for (int i = 0; i < device_count; i++) {
        CUdevice dev;
        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        if (ret < 0)
            continue;

        CUuuid uuid;
        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        if (ret < 0)
            continue;

        if (memcmp(gpu->uuid, uuid.bytes, sizeof (gpu->uuid)) == 0) {
            display_dev = dev;
            break;
        }
    }

    if (display_dev == -1) {
        MP_ERR(hw, "Could not match Vulkan display device in CUDA.\n");
        return false;
    }

    ret = CHECK_CU(cu->cuCtxCreate(&p->display_ctx, CU_CTX_SCHED_BLOCKING_SYNC,
                                   display_dev));
    if (ret < 0)
        return false;

    p->decode_ctx = p->display_ctx;

    p->ext_init = cuda_ext_vk_init;
    p->ext_uninit = cuda_ext_vk_uninit;
    p->ext_wait = cuda_ext_vk_wait;
    p->ext_signal = cuda_ext_vk_signal;

    return true;
}