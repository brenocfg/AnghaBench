#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct render_backend {struct priv* priv; } ;
struct TYPE_4__ {int w; int h; } ;
struct ra_tex {TYPE_1__ params; } ;
struct priv {TYPE_3__* context; } ;
typedef  int /*<<< orphan*/  mpv_render_param ;
struct TYPE_6__ {TYPE_2__* fns; } ;
struct TYPE_5__ {int (* wrap_fbo ) (TYPE_3__*,int /*<<< orphan*/ *,struct ra_tex**) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *,struct ra_tex**) ; 

__attribute__((used)) static int get_target_size(struct render_backend *ctx, mpv_render_param *params,
                           int *out_w, int *out_h)
{
    struct priv *p = ctx->priv;

    // Mapping the surface is cheap, better than adding new backend entrypoints.
    struct ra_tex *tex;
    int err = p->context->fns->wrap_fbo(p->context, params, &tex);
    if (err < 0)
        return err;
    *out_w = tex->params.w;
    *out_h = tex->params.h;
    return 0;
}