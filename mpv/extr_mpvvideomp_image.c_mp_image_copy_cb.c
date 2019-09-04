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
struct TYPE_2__ {int* bpp; int flags; } ;
struct mp_image {scalar_t__ imgfmt; scalar_t__ w; scalar_t__ h; int num_planes; int /*<<< orphan*/ * planes; TYPE_1__ fmt; int /*<<< orphan*/ * stride; } ;
typedef  int /*<<< orphan*/  memcpy_fn ;

/* Variables and functions */
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int MP_IMGFLAG_PAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_pic_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_image_is_writeable (struct mp_image*) ; 
 int mp_image_plane_h (struct mp_image*,int) ; 
 int mp_image_plane_w (struct mp_image*,int) ; 

__attribute__((used)) static void mp_image_copy_cb(struct mp_image *dst, struct mp_image *src,
                             memcpy_fn cpy)
{
    assert(dst->imgfmt == src->imgfmt);
    assert(dst->w == src->w && dst->h == src->h);
    assert(mp_image_is_writeable(dst));
    for (int n = 0; n < dst->num_planes; n++) {
        int line_bytes = (mp_image_plane_w(dst, n) * dst->fmt.bpp[n] + 7) / 8;
        int plane_h = mp_image_plane_h(dst, n);
        memcpy_pic_cb(dst->planes[n], src->planes[n], line_bytes, plane_h,
                      dst->stride[n], src->stride[n], cpy);
    }
    if (dst->fmt.flags & MP_IMGFLAG_PAL)
        memcpy(dst->planes[1], src->planes[1], AVPALETTE_SIZE);
}