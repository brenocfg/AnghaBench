#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  osd; struct priv* priv; } ;
struct TYPE_6__ {int x0; int /*<<< orphan*/  y1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x1; } ;
struct mp_rect {void* y0; void* x0; } ;
struct priv {size_t front_buf; struct mp_image* last_input; TYPE_3__* cur_frame; struct framebuffer* bufs; int /*<<< orphan*/  osd; int /*<<< orphan*/  cur_frame_cropped; int /*<<< orphan*/  sws; TYPE_2__ dst; struct mp_rect src; scalar_t__ active; } ;
struct TYPE_5__ {int /*<<< orphan*/  align_y; int /*<<< orphan*/  align_x; } ;
struct mp_image {int /*<<< orphan*/  pts; TYPE_1__ fmt; } ;
struct framebuffer {int /*<<< orphan*/  stride; int /*<<< orphan*/  map; } ;
typedef  struct mp_image mp_image_t ;
struct TYPE_7__ {int w; int /*<<< orphan*/ * stride; int /*<<< orphan*/  h; int /*<<< orphan*/ * planes; } ;

/* Variables and functions */
 int BYTES_PER_PIXEL ; 
 void* MP_ALIGN_DOWN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_clear (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_crop_rc (struct mp_image*,struct mp_rect) ; 
 int /*<<< orphan*/  mp_sws_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  osd_draw_on_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

__attribute__((used)) static void draw_image(struct vo *vo, mp_image_t *mpi)
{
    struct priv *p = vo->priv;

    if (p->active) {
        if (mpi) {
            struct mp_image src = *mpi;
            struct mp_rect src_rc = p->src;
            src_rc.x0 = MP_ALIGN_DOWN(src_rc.x0, mpi->fmt.align_x);
            src_rc.y0 = MP_ALIGN_DOWN(src_rc.y0, mpi->fmt.align_y);
            mp_image_crop_rc(&src, src_rc);

            mp_image_clear(p->cur_frame, 0, 0, p->cur_frame->w, p->dst.y0);
            mp_image_clear(p->cur_frame, 0, p->dst.y1, p->cur_frame->w, p->cur_frame->h);
            mp_image_clear(p->cur_frame, 0, p->dst.y0, p->dst.x0, p->dst.y1);
            mp_image_clear(p->cur_frame, p->dst.x1, p->dst.y0, p->cur_frame->w, p->dst.y1);

            mp_sws_scale(p->sws, p->cur_frame_cropped, &src);
            osd_draw_on_image(vo->osd, p->osd, src.pts, 0, p->cur_frame);
        } else {
            mp_image_clear(p->cur_frame, 0, 0, p->cur_frame->w, p->cur_frame->h);
            osd_draw_on_image(vo->osd, p->osd, 0, 0, p->cur_frame);
        }

        struct framebuffer *front_buf = &p->bufs[p->front_buf];
        memcpy_pic(front_buf->map, p->cur_frame->planes[0],
                   p->cur_frame->w * BYTES_PER_PIXEL, p->cur_frame->h,
                   front_buf->stride,
                   p->cur_frame->stride[0]);
    }

    if (mpi != p->last_input) {
        talloc_free(p->last_input);
        p->last_input = mpi;
    }
}