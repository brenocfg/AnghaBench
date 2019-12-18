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
struct vo {int /*<<< orphan*/  osd; struct priv* priv; } ;
struct mp_rect {void* y0; void* x0; } ;
struct priv {struct mp_image* original_image; int /*<<< orphan*/  osd; int /*<<< orphan*/  sws; struct mp_rect src; int /*<<< orphan*/  current_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  align_y; int /*<<< orphan*/  align_x; } ;
struct mp_image {int /*<<< orphan*/  pts; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__ fmt; } ;
typedef  struct mp_image mp_image_t ;

/* Variables and functions */
 void* MP_ALIGN_DOWN (void*,int /*<<< orphan*/ ) ; 
 struct mp_image get_x_buffer (struct priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_clear (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_crop_rc (struct mp_image*,struct mp_rect) ; 
 int /*<<< orphan*/  mp_sws_scale (int /*<<< orphan*/ ,struct mp_image*,struct mp_image*) ; 
 int /*<<< orphan*/  osd_draw_on_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 int /*<<< orphan*/  wait_for_completion (struct vo*,int) ; 

__attribute__((used)) static void draw_image(struct vo *vo, mp_image_t *mpi)
{
    struct priv *p = vo->priv;

    wait_for_completion(vo, 1);

    struct mp_image img = get_x_buffer(p, p->current_buf);

    if (mpi) {
        struct mp_image src = *mpi;
        struct mp_rect src_rc = p->src;
        src_rc.x0 = MP_ALIGN_DOWN(src_rc.x0, src.fmt.align_x);
        src_rc.y0 = MP_ALIGN_DOWN(src_rc.y0, src.fmt.align_y);
        mp_image_crop_rc(&src, src_rc);

        mp_sws_scale(p->sws, &img, &src);
    } else {
        mp_image_clear(&img, 0, 0, img.w, img.h);
    }

    osd_draw_on_image(vo->osd, p->osd, mpi ? mpi->pts : 0, 0, &img);

    if (mpi != p->original_image) {
        talloc_free(p->original_image);
        p->original_image = mpi;
    }
}