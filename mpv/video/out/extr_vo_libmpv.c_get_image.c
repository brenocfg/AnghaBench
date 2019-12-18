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
struct vo_priv {struct mpv_render_context* ctx; } ;
struct vo {struct vo_priv* priv; } ;
struct mpv_render_context {scalar_t__ dr; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 struct mp_image* dr_helper_get_image (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static struct mp_image *get_image(struct vo *vo, int imgfmt, int w, int h,
                                  int stride_align)
{
    struct vo_priv *p = vo->priv;
    struct mpv_render_context *ctx = p->ctx;

    if (ctx->dr)
        return dr_helper_get_image(ctx->dr, imgfmt, w, h, stride_align);

    return NULL;
}