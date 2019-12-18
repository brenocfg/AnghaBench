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
struct vo {int dummy; } ;
struct ra_ctx {struct vo* vo; struct priv* priv; } ;
struct priv {int sc_width; int sc_height; int /*<<< orphan*/  dxgi_swapchain; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DXGI_FORMAT_UNKNOWN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDXGISwapChain_ResizeBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*,...) ; 
 int /*<<< orphan*/  d3d11_backbuffer_get (struct ra_ctx*) ; 
 int /*<<< orphan*/  d3d11_backbuffer_release (struct ra_ctx*) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_sizes (struct ra_ctx*) ; 

__attribute__((used)) static void d3d11_backbuffer_resize(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;
    HRESULT hr;

    int old_sc_width = p->sc_width;
    int old_sc_height = p->sc_height;

    update_sizes(ctx);
    // Avoid unnecessary resizing
    if (old_sc_width == p->sc_width && old_sc_height == p->sc_height)
        return;

    // All references to backbuffers must be released before ResizeBuffers
    // (including references held by ANGLE)
    d3d11_backbuffer_release(ctx);

    // The DirectX runtime may report errors related to the device like
    // DXGI_ERROR_DEVICE_REMOVED at this point
    hr = IDXGISwapChain_ResizeBuffers(p->dxgi_swapchain, 0, p->sc_width,
        p->sc_height, DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(hr))
        MP_FATAL(vo, "Couldn't resize swapchain: %s\n", mp_HRESULT_to_str(hr));

    if (!d3d11_backbuffer_get(ctx))
        MP_FATAL(vo, "Couldn't get back buffer after resize\n");
}