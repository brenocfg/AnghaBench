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
struct ra_tex {int dummy; } ;
struct ra_ctx {int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  swapchain; } ;
typedef  int /*<<< orphan*/  ID3D11Texture2D ;
typedef  int /*<<< orphan*/  ID3D11Resource ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDXGISwapChain_GetBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_ID3D11Texture2D ; 
 int /*<<< orphan*/  MP_ERR (struct ra_ctx*,char*) ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ *) ; 
 struct ra_tex* ra_d3d11_wrap_tex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ra_tex *get_backbuffer(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    ID3D11Texture2D *backbuffer = NULL;
    struct ra_tex *tex = NULL;
    HRESULT hr;

    hr = IDXGISwapChain_GetBuffer(p->swapchain, 0, &IID_ID3D11Texture2D,
                                  (void**)&backbuffer);
    if (FAILED(hr)) {
        MP_ERR(ctx, "Couldn't get swapchain image\n");
        goto done;
    }

    tex = ra_d3d11_wrap_tex(ctx->ra, (ID3D11Resource *)backbuffer);
done:
    SAFE_RELEASE(backbuffer);
    return tex;
}