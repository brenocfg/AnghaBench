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
struct TYPE_4__ {int /*<<< orphan*/  color; } ;
struct TYPE_3__ {int flags; } ;
struct mp_image {int imgfmt; int w; int h; int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; TYPE_2__ params; TYPE_1__ fmt; } ;
struct mp_draw_sub_cache {struct mp_image upsample_temp; struct mp_image* upsample_img; } ;

/* Variables and functions */
 int IMGFMT_420P ; 
 int IMGFMT_444P ; 
 int /*<<< orphan*/  IMGFMT_Y8 ; 
 int MP_IMGFLAG_YUV ; 
 int /*<<< orphan*/  SWS_POINT ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mp_image* mp_image_alloc (int,int,int) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int,int) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_swscale (struct mp_image*,struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 int /*<<< orphan*/  talloc_steal (struct mp_draw_sub_cache*,struct mp_image*) ; 

__attribute__((used)) static struct mp_image *chroma_up(struct mp_draw_sub_cache *cache, int imgfmt,
                                  struct mp_image *src)
{
    if (src->imgfmt == imgfmt)
        return src;

    if (!cache->upsample_img || cache->upsample_img->imgfmt != imgfmt ||
        cache->upsample_img->w < src->w || cache->upsample_img->h < src->h)
    {
        talloc_free(cache->upsample_img);
        cache->upsample_img = mp_image_alloc(imgfmt, src->w, src->h);
        talloc_steal(cache, cache->upsample_img);
        if (!cache->upsample_img)
            return NULL;
    }

    cache->upsample_temp = *cache->upsample_img;
    struct mp_image *temp = &cache->upsample_temp;
    mp_image_set_size(temp, src->w, src->h);

    // The temp image is always YUV, but src not necessarily.
    // Reduce amount of conversions in YUV case (upsampling/shifting only)
    if (src->fmt.flags & MP_IMGFLAG_YUV)
        temp->params.color = src->params.color;

    if (src->imgfmt == IMGFMT_420P) {
        assert(imgfmt == IMGFMT_444P);
        // Faster upsampling: keep Y plane, upsample chroma planes only
        // The whole point is not having swscale copy the Y plane
        struct mp_image t_dst = *temp;
        mp_image_setfmt(&t_dst, IMGFMT_Y8);
        mp_image_set_size(&t_dst, temp->w, temp->h);
        struct mp_image t_src = t_dst;
        mp_image_set_size(&t_src, src->w >> 1, src->h >> 1);
        for (int c = 0; c < 2; c++) {
            t_dst.planes[0] = temp->planes[1 + c];
            t_dst.stride[0] = temp->stride[1 + c];
            t_src.planes[0] = src->planes[1 + c];
            t_src.stride[0] = src->stride[1 + c];
            mp_image_swscale(&t_dst, &t_src, SWS_POINT);
        }
        temp->planes[0] = src->planes[0];
        temp->stride[0] = src->stride[0];
    } else {
        mp_image_swscale(temp, src, SWS_POINT);
    }

    return temp;
}