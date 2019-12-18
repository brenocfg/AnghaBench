#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/ * device; } ;
struct TYPE_8__ {TYPE_2__* hwctx; } ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  TYPE_1__ AVHWDeviceContext ;
typedef  TYPE_2__ AVD3D11VADeviceContext ;
typedef  TYPE_3__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_HWDEVICE_TYPE_D3D11VA ; 
 int /*<<< orphan*/  ID3D11Device_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_3__**) ; 
 TYPE_3__* av_hwdevice_ctx_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ av_hwdevice_ctx_init (TYPE_3__*) ; 

AVBufferRef *d3d11_wrap_device_ref(ID3D11Device *device)
{
    AVBufferRef *device_ref = av_hwdevice_ctx_alloc(AV_HWDEVICE_TYPE_D3D11VA);
    if (!device_ref)
        return NULL;

    AVHWDeviceContext *ctx = (void *)device_ref->data;
    AVD3D11VADeviceContext *hwctx = ctx->hwctx;

    ID3D11Device_AddRef(device);
    hwctx->device = device;

    if (av_hwdevice_ctx_init(device_ref) < 0)
        av_buffer_unref(&device_ref);

    return device_ref;
}