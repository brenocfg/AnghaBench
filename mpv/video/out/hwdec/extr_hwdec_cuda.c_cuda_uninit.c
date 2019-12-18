#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {int /*<<< orphan*/  devs; struct cuda_hw_priv* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  av_device_ref; } ;
struct cuda_hw_priv {scalar_t__ decode_ctx; scalar_t__ display_ctx; TYPE_1__* cu; TYPE_2__ hwctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cuCtxDestroy ) (scalar_t__) ;} ;
typedef  TYPE_1__ CudaFunctions ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cuda_free_functions (TYPE_1__**) ; 
 int /*<<< orphan*/  hwdec_devices_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 

__attribute__((used)) static void cuda_uninit(struct ra_hwdec *hw)
{
    struct cuda_hw_priv *p = hw->priv;
    CudaFunctions *cu = p->cu;

    hwdec_devices_remove(hw->devs, &p->hwctx);
    av_buffer_unref(&p->hwctx.av_device_ref);

    if (p->decode_ctx && p->decode_ctx != p->display_ctx)
        CHECK_CU(cu->cuCtxDestroy(p->decode_ctx));

    if (p->display_ctx)
        CHECK_CU(cu->cuCtxDestroy(p->display_ctx));

    cuda_free_functions(&p->cu);
}