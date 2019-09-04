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
struct mp_image {scalar_t__ w; scalar_t__ h; scalar_t__ imgfmt; scalar_t__* planes; int /*<<< orphan*/ * stride; } ;

/* Variables and functions */
 scalar_t__ IMGFMT_420P ; 
 scalar_t__ IMGFMT_444P ; 
 int /*<<< orphan*/  IMGFMT_Y8 ; 
 int /*<<< orphan*/  SWS_AREA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int,int) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_swscale (struct mp_image*,struct mp_image*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chroma_down(struct mp_image *old_src, struct mp_image *temp)
{
    assert(old_src->w == temp->w && old_src->h == temp->h);
    if (temp != old_src) {
        if (old_src->imgfmt == IMGFMT_420P) {
            // Downsampling, skipping the Y plane (see chroma_up())
            assert(temp->imgfmt == IMGFMT_444P);
            assert(temp->planes[0] == old_src->planes[0]);
            struct mp_image t_dst = *temp;
            mp_image_setfmt(&t_dst, IMGFMT_Y8);
            mp_image_set_size(&t_dst, old_src->w >> 1, old_src->h >> 1);
            struct mp_image t_src = t_dst;
            mp_image_set_size(&t_src, temp->w, temp->h);
            for (int c = 0; c < 2; c++) {
                t_dst.planes[0] = old_src->planes[1 + c];
                t_dst.stride[0] = old_src->stride[1 + c];
                t_src.planes[0] = temp->planes[1 + c];
                t_src.stride[0] = temp->stride[1 + c];
                mp_image_swscale(&t_dst, &t_src, SWS_AREA);
            }
        } else {
            mp_image_swscale(old_src, temp, SWS_AREA); // chroma down
        }
    }
}