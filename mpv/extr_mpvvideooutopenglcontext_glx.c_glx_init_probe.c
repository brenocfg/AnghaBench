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
struct ra_ctx {struct priv* priv; } ;
struct TYPE_2__ {int mpgl_caps; } ;
struct priv {TYPE_1__ gl; } ;

/* Variables and functions */
 int MPGL_CAP_VDPAU ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_ctx*,char*) ; 
 int /*<<< orphan*/  glx_init (struct ra_ctx*) ; 
 int /*<<< orphan*/  glx_uninit (struct ra_ctx*) ; 

__attribute__((used)) static bool glx_init_probe(struct ra_ctx *ctx)
{
    if (!glx_init(ctx))
        return false;

    struct priv *p = ctx->priv;
    if (!(p->gl.mpgl_caps & MPGL_CAP_VDPAU)) {
        MP_VERBOSE(ctx, "No vdpau support found - probing more things.\n");
        glx_uninit(ctx);
        return false;
    }

    return true;
}