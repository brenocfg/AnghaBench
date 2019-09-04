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
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* DXLockObjectsNV ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DXUnlockObjectsNV ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
struct priv {int lost_device; int /*<<< orphan*/  rtarget_h; int /*<<< orphan*/  device_h; int /*<<< orphan*/  device; int /*<<< orphan*/  backbuffer; int /*<<< orphan*/  rtarget; TYPE_1__ gl; } ;
typedef  int HRESULT ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
#define  D3DERR_DEVICEHUNG 129 
#define  D3DERR_DEVICELOST 128 
 int /*<<< orphan*/  D3DTEXF_NONE ; 
 scalar_t__ FAILED (int) ; 
 int IDirect3DDevice9Ex_PresentEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IDirect3DDevice9Ex_StretchRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dxgl_reset (struct ra_ctx*) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int) ; 
 int /*<<< orphan*/  mp_LastError_to_str () ; 
 int /*<<< orphan*/  pump_message_loop () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dxgl_swap_buffers(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    GL *gl = &p->gl;
    HRESULT hr;

    pump_message_loop();

    // If the device is still lost, try to reset it again
    if (p->lost_device)
        dxgl_reset(ctx);
    if (p->lost_device)
        return;

    if (!gl->DXUnlockObjectsNV(p->device_h, 1, &p->rtarget_h)) {
        MP_ERR(ctx->vo, "Couldn't unlock rendertarget for present: %s\n",
               mp_LastError_to_str());
        return;
    }

    // Blit the OpenGL rendertarget to the backbuffer
    hr = IDirect3DDevice9Ex_StretchRect(p->device, p->rtarget, NULL,
                                        p->backbuffer, NULL, D3DTEXF_NONE);
    if (FAILED(hr)) {
        MP_ERR(ctx->vo, "Couldn't stretchrect for present: %s\n",
               mp_HRESULT_to_str(hr));
        return;
    }

    hr = IDirect3DDevice9Ex_PresentEx(p->device, NULL, NULL, NULL, NULL, 0);
    switch (hr) {
    case D3DERR_DEVICELOST:
    case D3DERR_DEVICEHUNG:
        MP_VERBOSE(ctx->vo, "Direct3D device lost! Resetting.\n");
        p->lost_device = true;
        dxgl_reset(ctx);
        return;
    default:
        if (FAILED(hr))
            MP_ERR(ctx->vo, "Failed to present: %s\n", mp_HRESULT_to_str(hr));
    }

    if (!gl->DXLockObjectsNV(p->device_h, 1, &p->rtarget_h)) {
        MP_ERR(ctx->vo, "Couldn't lock rendertarget after present: %s\n",
               mp_LastError_to_str());
    }
}