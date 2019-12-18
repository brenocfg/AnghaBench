#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xvctx {TYPE_1__* original_image; int /*<<< orphan*/  current_buf; scalar_t__ num_buffers; } ;
struct vo {int /*<<< orphan*/  osd; int /*<<< orphan*/  params; struct xvctx* priv; } ;
struct mp_osd_res {int dummy; } ;
struct mp_image {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_5__ {int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ mp_image_t ;

/* Variables and functions */
 struct mp_image get_xv_buffer (struct vo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_clear (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_copy (struct mp_image*,TYPE_1__*) ; 
 int /*<<< orphan*/  osd_draw_on_image (int /*<<< orphan*/ ,struct mp_osd_res,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_image*) ; 
 struct mp_osd_res osd_res_from_image_params (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (struct vo*,scalar_t__) ; 

__attribute__((used)) static void draw_image(struct vo *vo, mp_image_t *mpi)
{
    struct xvctx *ctx = vo->priv;

    wait_for_completion(vo, ctx->num_buffers - 1);

    struct mp_image xv_buffer = get_xv_buffer(vo, ctx->current_buf);
    if (mpi) {
        mp_image_copy(&xv_buffer, mpi);
    } else {
        mp_image_clear(&xv_buffer, 0, 0, xv_buffer.w, xv_buffer.h);
    }

    struct mp_osd_res res = osd_res_from_image_params(vo->params);
    osd_draw_on_image(vo->osd, res, mpi ? mpi->pts : 0, 0, &xv_buffer);

    if (mpi != ctx->original_image) {
        talloc_free(ctx->original_image);
        ctx->original_image = mpi;
    }
}