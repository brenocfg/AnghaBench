#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float w; float h; } ;
struct szexp_ctx {TYPE_4__ img; struct gl_video* p; } ;
struct TYPE_9__ {float x1; float x0; float y1; float y0; } ;
struct TYPE_8__ {float** m; } ;
struct TYPE_7__ {float x1; float x0; float y1; float y0; } ;
struct gl_video {int num_saved_imgs; TYPE_6__* saved_imgs; TYPE_3__ dst_rect; TYPE_2__ texture_offset; TYPE_1__ src_rect; } ;
struct bstr {int dummy; } ;
struct TYPE_11__ {float w; float h; } ;
struct TYPE_12__ {char* name; TYPE_5__ img; } ;

/* Variables and functions */
 scalar_t__ bstr_equals0 (struct bstr,char*) ; 

__attribute__((used)) static bool szexp_lookup(void *priv, struct bstr var, float size[2])
{
    struct szexp_ctx *ctx = priv;
    struct gl_video *p = ctx->p;

    if (bstr_equals0(var, "NATIVE_CROPPED")) {
        size[0] = (p->src_rect.x1 - p->src_rect.x0) * p->texture_offset.m[0][0];
        size[1] = (p->src_rect.y1 - p->src_rect.y0) * p->texture_offset.m[1][1];
        return true;
    }

    // The size of OUTPUT is determined. It could be useful for certain
    // user shaders to skip passes.
    if (bstr_equals0(var, "OUTPUT")) {
        size[0] = p->dst_rect.x1 - p->dst_rect.x0;
        size[1] = p->dst_rect.y1 - p->dst_rect.y0;
        return true;
    }

    // HOOKED is a special case
    if (bstr_equals0(var, "HOOKED")) {
        size[0] = ctx->img.w;
        size[1] = ctx->img.h;
        return true;
    }

    for (int o = 0; o < p->num_saved_imgs; o++) {
        if (bstr_equals0(var, p->saved_imgs[o].name)) {
            size[0] = p->saved_imgs[o].img.w;
            size[1] = p->saved_imgs[o].img.h;
            return true;
        }
    }

    return false;
}