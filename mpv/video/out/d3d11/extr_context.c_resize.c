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
struct ra_ctx {TYPE_1__* vo; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  backbuffer; int /*<<< orphan*/  swapchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  dheight; int /*<<< orphan*/  dwidth; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DXGI_FORMAT_UNKNOWN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDXGISwapChain_ResizeBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_FATAL (struct ra_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_backbuffer (struct ra_ctx*) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool resize(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    HRESULT hr;

    ra_tex_free(ctx->ra, &p->backbuffer);

    hr = IDXGISwapChain_ResizeBuffers(p->swapchain, 0, ctx->vo->dwidth,
        ctx->vo->dheight, DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(hr)) {
        MP_FATAL(ctx, "Couldn't resize swapchain: %s\n", mp_HRESULT_to_str(hr));
        return false;
    }

    p->backbuffer = get_backbuffer(ctx);

    return true;
}