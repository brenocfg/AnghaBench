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
typedef  int /*<<< orphan*/  uint8_t ;
struct sub_bitmaps {int num_parts; struct sub_bitmap* parts; TYPE_1__* packed; int /*<<< orphan*/  format; int /*<<< orphan*/  change_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  color; } ;
struct sub_bitmap {scalar_t__ w; scalar_t__ h; scalar_t__ x; scalar_t__ y; int dw; scalar_t__ dh; int stride; int src_y; int src_x; TYPE_2__ libass; int /*<<< orphan*/ * bitmap; } ;
struct mp_rect {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; } ;
struct mp_ass_packer {struct sub_bitmap* rgba_imgs; } ;
struct TYPE_3__ {int* stride; scalar_t__* planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFMT_BGRA ; 
 int MP_SUB_BB_LIST_MAX ; 
 int /*<<< orphan*/  SUBBITMAP_RGBA ; 
 int /*<<< orphan*/  draw_ass_rgba (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_pic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int mp_get_sub_bb_list (struct sub_bitmaps*,struct mp_rect*,int) ; 
 int /*<<< orphan*/  pack (struct mp_ass_packer*,struct sub_bitmaps*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pack_rgba(struct mp_ass_packer *p, struct sub_bitmaps *res)
{
    struct mp_rect bb_list[MP_SUB_BB_LIST_MAX];
    int num_bb = mp_get_sub_bb_list(res, bb_list, MP_SUB_BB_LIST_MAX);

    struct sub_bitmaps imgs = {
        .change_id = res->change_id,
        .format = SUBBITMAP_RGBA,
        .parts = p->rgba_imgs,
        .num_parts = num_bb,
    };

    for (int n = 0; n < imgs.num_parts; n++) {
        imgs.parts[n].w = bb_list[n].x1 - bb_list[n].x0;
        imgs.parts[n].h = bb_list[n].y1 - bb_list[n].y0;
    }

    if (!pack(p, &imgs, IMGFMT_BGRA))
        return false;

    for (int n = 0; n < num_bb; n++) {
        struct mp_rect bb = bb_list[n];
        struct sub_bitmap *b = &imgs.parts[n];

        b->x = bb.x0;
        b->y = bb.y0;
        b->w = b->dw = bb.x1 - bb.x0;
        b->h = b->dh = bb.y1 - bb.y0;
        b->stride = imgs.packed->stride[0];
        b->bitmap = (uint8_t *)imgs.packed->planes[0] +
                    b->stride * b->src_y + b->src_x * 4;

        memset_pic(b->bitmap, 0, b->w * 4, b->h, b->stride);

        for (int i = 0; i < res->num_parts; i++) {
            struct sub_bitmap *s = &res->parts[i];

            // Assume mp_get_sub_bb_list() never splits sub bitmaps
            // So we don't clip/adjust the size of the sub bitmap
            if (s->x > bb.x1 || s->x + s->w < bb.x0 ||
                s->y > bb.y1 || s->y + s->h < bb.y0)
                continue;

            draw_ass_rgba(s->bitmap, s->w, s->h, s->stride,
                          b->bitmap, b->stride,
                          s->x - bb.x0, s->y - bb.y0,
                          s->libass.color);
        }
    }

    *res = imgs;
    return true;
}