#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xvctx {scalar_t__ xv_format; scalar_t__ cached_csp; int /*<<< orphan*/  image_format; int /*<<< orphan*/  image_height; int /*<<< orphan*/  image_width; TYPE_2__** xvimage; } ;
struct vo {struct mp_image_params* params; struct xvctx* priv; } ;
struct TYPE_3__ {scalar_t__ space; } ;
struct mp_image_params {TYPE_1__ color; } ;
struct mp_image {int num_planes; int /*<<< orphan*/ * stride; scalar_t__* planes; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pitches; scalar_t__* offsets; scalar_t__ data; } ;
typedef  TYPE_2__ XvImage ;

/* Variables and functions */
 scalar_t__ MP_FOURCC_YV12 ; 
 int /*<<< orphan*/  mp_image_set_attributes (struct mp_image*,struct mp_image_params*) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mp_image get_xv_buffer(struct vo *vo, int buf_index)
{
    struct xvctx *ctx = vo->priv;
    XvImage *xv_image = ctx->xvimage[buf_index];

    struct mp_image img = {0};
    mp_image_set_size(&img, ctx->image_width, ctx->image_height);
    mp_image_setfmt(&img, ctx->image_format);

    bool swapuv = ctx->xv_format == MP_FOURCC_YV12;
    for (int n = 0; n < img.num_planes; n++) {
        int sn = n > 0 &&  swapuv ? (n == 1 ? 2 : 1) : n;
        img.planes[n] = xv_image->data + xv_image->offsets[sn];
        img.stride[n] = xv_image->pitches[sn];
    }

    if (vo->params) {
        struct mp_image_params params = *vo->params;
        if (ctx->cached_csp)
            params.color.space = ctx->cached_csp;
        mp_image_set_attributes(&img, &params);
    }

    return img;
}