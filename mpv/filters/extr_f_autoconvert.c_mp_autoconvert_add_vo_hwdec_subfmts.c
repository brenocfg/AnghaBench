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
struct priv {int num_imgfmts; int* imgfmts; int* subfmts; int vo_convert; } ;
struct mp_hwdec_devices {int dummy; } ;
struct mp_hwdec_ctx {int hw_imgfmt; scalar_t__* supported_formats; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (int*,int,int) ; 
 int /*<<< orphan*/  assert (struct mp_hwdec_devices*) ; 
 struct mp_hwdec_ctx* hwdec_devices_get_n (struct mp_hwdec_devices*,int) ; 
 int /*<<< orphan*/  mp_autoconvert_add_imgfmt (struct mp_autoconvert*,int,scalar_t__) ; 

void mp_autoconvert_add_vo_hwdec_subfmts(struct mp_autoconvert *c,
                                         struct mp_hwdec_devices *devs)
{
    struct priv *p = c->f->priv;
    assert(devs);

    int prev_format = 0;

    for (int n = 0; ; n++) {
        struct mp_hwdec_ctx *ctx = hwdec_devices_get_n(devs, n);
        if (!ctx)
            break;
        if (!ctx->hw_imgfmt || !ctx->supported_formats)
            continue;
        // Very hacky: don't let d3d11-egl-rgb overwrite d3d11-egl
        if (ctx->hw_imgfmt == prev_format)
            continue;
        prev_format = ctx->hw_imgfmt;
        // Stupidity: VOs export imgfmt only, so subfmt is always 0. Remove it
        // to fix it up.
        for (int i = 0; i < p->num_imgfmts; i++) {
            if (p->imgfmts[i] != ctx->hw_imgfmt)
                continue;

            int count = p->num_imgfmts;
            MP_TARRAY_REMOVE_AT(p->imgfmts, count, i);
            count = p->num_imgfmts;
            MP_TARRAY_REMOVE_AT(p->subfmts, count, i);
            p->num_imgfmts -= 1;
            break;
        }
        for (int i = 0; ctx->supported_formats[i]; i++)
            mp_autoconvert_add_imgfmt(c, ctx->hw_imgfmt, ctx->supported_formats[i]);
    }

    p->vo_convert = true;
}