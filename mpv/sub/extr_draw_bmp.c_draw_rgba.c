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
typedef  int /*<<< orphan*/  uint8_t ;
struct sub_bitmaps {int num_parts; struct sub_bitmap* parts; } ;
struct sub_bitmap {int w; int h; } ;
struct part {TYPE_1__* imgs; } ;
struct mp_rect {int dummy; } ;
struct mp_image {int* stride; int num_planes; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/ ** planes; } ;
struct mp_draw_sub_cache {int dummy; } ;
struct TYPE_2__ {struct mp_image* a; struct mp_image* i; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct part*) ; 
 int /*<<< orphan*/  blend_src_alpha (int /*<<< orphan*/ *,int,void*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blend_src_dst_mul (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct part* get_cache (struct mp_draw_sub_cache*,struct sub_bitmaps*,struct mp_image*) ; 
 int /*<<< orphan*/  get_sub_area (struct mp_rect,struct mp_image*,struct sub_bitmap*,struct mp_image*,int*,int*) ; 
 int /*<<< orphan*/  scale_sb_rgba (struct sub_bitmap*,struct mp_image*,struct mp_image**,struct mp_image**) ; 
 void* talloc_steal (struct part*,struct mp_image*) ; 

__attribute__((used)) static void draw_rgba(struct mp_draw_sub_cache *cache, struct mp_rect bb,
                      struct mp_image *temp, int bits,
                      struct sub_bitmaps *sbs)
{
    struct part *part = get_cache(cache, sbs, temp);
    assert(part);

    for (int i = 0; i < sbs->num_parts; ++i) {
        struct sub_bitmap *sb = &sbs->parts[i];

        if (sb->w < 1 || sb->h < 1)
            continue;

        struct mp_image dst;
        int src_x, src_y;
        if (!get_sub_area(bb, temp, sb, &dst, &src_x, &src_y))
            continue;

        struct mp_image *sbi = part->imgs[i].i;
        struct mp_image *sba = part->imgs[i].a;

        if (!(sbi && sba))
            scale_sb_rgba(sb, temp, &sbi, &sba);
        // on OOM, skip drawing
        if (!(sbi && sba))
            continue;

        int bytes = (bits + 7) / 8;
        uint8_t *alpha_p = sba->planes[0] + src_y * sba->stride[0] + src_x;
        for (int p = 0; p < (temp->num_planes > 2 ? 3 : 1); p++) {
            void *src = sbi->planes[p] + src_y * sbi->stride[p] + src_x * bytes;
            blend_src_alpha(dst.planes[p], dst.stride[p], src, sbi->stride[p],
                            alpha_p, sba->stride[0], dst.w, dst.h, bytes);
        }
        if (temp->num_planes >= 4) {
            blend_src_dst_mul(dst.planes[3], dst.stride[3], alpha_p,
                              sba->stride[0], 255, dst.w, dst.h, bytes);
        }

        part->imgs[i].i = talloc_steal(part, sbi);
        part->imgs[i].a = talloc_steal(part, sba);
    }
}