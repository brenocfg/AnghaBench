#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec_mapper {TYPE_5__** tex; TYPE_2__* src; TYPE_1__* owner; struct cuda_mapper_priv* priv; } ;
struct TYPE_18__ {int num_planes; } ;
struct cuda_mapper_priv {TYPE_9__ layout; int /*<<< orphan*/ * cu_array; int /*<<< orphan*/  display_ctx; } ;
struct cuda_hw_priv {scalar_t__ do_full_sync; int /*<<< orphan*/  (* ext_signal ) (struct ra_hwdec_mapper*,int) ;int /*<<< orphan*/  (* ext_wait ) (struct ra_hwdec_mapper*,int) ;TYPE_6__* cu; } ;
struct TYPE_17__ {int WidthInBytes; int /*<<< orphan*/  Height; int /*<<< orphan*/  dstArray; int /*<<< orphan*/  dstMemoryType; int /*<<< orphan*/  srcY; int /*<<< orphan*/  srcPitch; int /*<<< orphan*/  srcDevice; int /*<<< orphan*/  srcMemoryType; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuStreamSynchronize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuMemcpy2DAsync ) (TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_3__* format; } ;
struct TYPE_15__ {TYPE_4__ params; } ;
struct TYPE_13__ {int pixel_size; } ;
struct TYPE_12__ {int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; } ;
struct TYPE_11__ {struct cuda_hw_priv* priv; } ;
typedef  TYPE_6__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUdeviceptr ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  TYPE_7__ CUDA_MEMCPY2D ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_MEMORYTYPE_ARRAY ; 
 int /*<<< orphan*/  CU_MEMORYTYPE_DEVICE ; 
 int /*<<< orphan*/  mp_image_plane_h (TYPE_9__*,int) ; 
 int mp_image_plane_w (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ra_hwdec_mapper*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ra_hwdec_mapper*,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mapper_map(struct ra_hwdec_mapper *mapper)
{
    struct cuda_mapper_priv *p = mapper->priv;
    struct cuda_hw_priv *p_owner = mapper->owner->priv;
    CudaFunctions *cu = p_owner->cu;
    CUcontext dummy;
    int ret = 0, eret = 0;

    ret = CHECK_CU(cu->cuCtxPushCurrent(p->display_ctx));
    if (ret < 0)
        return ret;

    for (int n = 0; n < p->layout.num_planes; n++) {
        if (p_owner->ext_wait) {
            if (!p_owner->ext_wait(mapper, n))
                goto error;
        }

        CUDA_MEMCPY2D cpy = {
            .srcMemoryType = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)mapper->src->planes[n],
            .srcPitch      = mapper->src->stride[n],
            .srcY          = 0,
            .dstMemoryType = CU_MEMORYTYPE_ARRAY,
            .dstArray      = p->cu_array[n],
            .WidthInBytes  = mp_image_plane_w(&p->layout, n) *
                             mapper->tex[n]->params.format->pixel_size,
            .Height        = mp_image_plane_h(&p->layout, n),
        };

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, 0));
        if (ret < 0)
            goto error;

        if (p_owner->ext_signal) {
            if (!p_owner->ext_signal(mapper, n))
                goto error;
        }
    }
    if (p_owner->do_full_sync)
        CHECK_CU(cu->cuStreamSynchronize(0));

 error:
   eret = CHECK_CU(cu->cuCtxPopCurrent(&dummy));
   if (eret < 0)
       return eret;

   return ret;
}