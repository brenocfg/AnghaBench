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
struct vo_frame {int dummy; } ;
struct ra_swapchain {TYPE_1__* ctx; } ;
struct priv {scalar_t__ d3d11_context; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_Flush (scalar_t__) ; 
 int ra_gl_ctx_submit_frame (struct ra_swapchain*,struct vo_frame const*) ; 

__attribute__((used)) static bool angle_submit_frame(struct ra_swapchain *sw,
                               const struct vo_frame *frame)
{
    struct priv *p = sw->ctx->priv;
    bool ret = ra_gl_ctx_submit_frame(sw, frame);
    if (p->d3d11_context) {
        // DXGI Present doesn't flush the immediate context, which can make
        // timers inaccurate, since the end queries might not be sent until the
        // next frame. Fix this by flushing the context now.
        ID3D11DeviceContext_Flush(p->d3d11_context);
    }
    return ret;
}