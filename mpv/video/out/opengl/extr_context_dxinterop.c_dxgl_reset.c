#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {TYPE_1__* vo; struct priv* priv; } ;
struct priv {scalar_t__ width; scalar_t__ height; scalar_t__ requested_swapinterval; scalar_t__ swapinterval; int lost_device; int /*<<< orphan*/  device; } ;
struct TYPE_3__ {scalar_t__ dwidth; scalar_t__ dheight; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_ResetEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 scalar_t__ d3d_size_dependent_create (struct ra_ctx*) ; 
 int /*<<< orphan*/  d3d_size_dependent_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  fill_presentparams (struct ra_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dxgl_reset(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    HRESULT hr;

    // Check if the device actually needs to be reset
    if (ctx->vo->dwidth == p->width && ctx->vo->dheight == p->height &&
        p->requested_swapinterval == p->swapinterval && !p->lost_device)
        return;

    d3d_size_dependent_destroy(ctx);

    D3DPRESENT_PARAMETERS pparams;
    fill_presentparams(ctx, &pparams);

    hr = IDirect3DDevice9Ex_ResetEx(p->device, &pparams, NULL);
    if (FAILED(hr)) {
        p->lost_device = true;
        MP_ERR(ctx->vo, "Couldn't reset device: %s\n", mp_HRESULT_to_str(hr));
        return;
    }

    if (d3d_size_dependent_create(ctx) < 0) {
        p->lost_device = true;
        MP_ERR(ctx->vo, "Couldn't recreate Direct3D objects after reset\n");
        return;
    }

    MP_VERBOSE(ctx->vo, "Direct3D device reset\n");
    p->width = ctx->vo->dwidth;
    p->height = ctx->vo->dheight;
    p->swapinterval = p->requested_swapinterval;
    p->lost_device = false;
}