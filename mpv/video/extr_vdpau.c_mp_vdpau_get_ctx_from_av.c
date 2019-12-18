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
struct mp_vdpau_ctx {int dummy; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ free; struct mp_vdpau_ctx* user_opaque; } ;
typedef  TYPE_1__ AVHWDeviceContext ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 scalar_t__ free_device_ref ; 

struct mp_vdpau_ctx *mp_vdpau_get_ctx_from_av(AVBufferRef *hw_device_ctx)
{
    AVHWDeviceContext *hwctx = (void *)hw_device_ctx->data;

    if (hwctx->free != free_device_ref)
        return NULL; // not ours

    return hwctx->user_opaque;
}