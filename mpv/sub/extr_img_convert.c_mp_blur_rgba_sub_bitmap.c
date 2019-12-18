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
struct sub_bitmap {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  stride; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mp_image {int /*<<< orphan*/ * planes; int /*<<< orphan*/ * stride; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFMT_BGRA ; 
 struct mp_image* mp_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_copy (struct mp_image*,struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_sw_blur_scale (struct mp_image*,struct mp_image*,double) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

void mp_blur_rgba_sub_bitmap(struct sub_bitmap *d, double gblur)
{
    struct mp_image *tmp1 = mp_image_alloc(IMGFMT_BGRA, d->w, d->h);
    if (tmp1) { // on OOM, skip region
        struct mp_image s = {0};
        mp_image_setfmt(&s, IMGFMT_BGRA);
        mp_image_set_size(&s, d->w, d->h);
        s.stride[0] = d->stride;
        s.planes[0] = d->bitmap;

        mp_image_copy(tmp1, &s);

        mp_image_sw_blur_scale(&s, tmp1, gblur);
    }
    talloc_free(tmp1);
}