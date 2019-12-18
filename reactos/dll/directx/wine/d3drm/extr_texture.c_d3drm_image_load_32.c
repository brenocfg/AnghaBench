#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int depth; int rgb; int bytes_per_line; unsigned char* buffer1; int red_mask; int green_mask; int blue_mask; int /*<<< orphan*/ * palette; scalar_t__ palette_size; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ D3DRMIMAGE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRMERR_BADALLOC ; 
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ d3drm_image_palettise (TYPE_1__*,unsigned char*,int,int,scalar_t__) ; 
 unsigned char* heap_alloc (int) ; 

__attribute__((used)) static HRESULT d3drm_image_load_32(D3DRMIMAGE *image, unsigned char *src_data,
        LONGLONG src_data_size, SIZE_T w, SIZE_T h, BOOL flip)
{
    unsigned char *dst_data, *src_ptr, *dst_ptr;
    SIZE_T src_pitch, dst_pitch, x, y;

    if (d3drm_image_palettise(image, src_data, w, h, flip))
        return D3DRM_OK;

    if (w > (~(SIZE_T)0 / 4) / h)
        return D3DRMERR_BADALLOC;

    src_pitch = flip ? -w * 3 : w * 3;
    dst_pitch = w * 4;

    if (!(dst_data = heap_alloc(dst_pitch * h)))
    {
        WARN("Failed to allocate image buffer.\n");
        return D3DRMERR_BADALLOC;
    }

    src_ptr = flip ? &src_data[(h - 1) * w * 3] : src_data;
    dst_ptr = dst_data;

    for (y = 0; y < h; ++y)
    {
        for (x = 0; x < w; ++x)
        {
            dst_ptr[x * 4 + 0] = src_ptr[x * 3 + 0];
            dst_ptr[x * 4 + 1] = src_ptr[x * 3 + 1];
            dst_ptr[x * 4 + 2] = src_ptr[x * 3 + 2];
            dst_ptr[x * 4 + 3] = 0xff;
        }

        src_ptr += src_pitch;
        dst_ptr += dst_pitch;
    }

    image->depth = 32;
    image->rgb = 1;
    image->bytes_per_line = dst_pitch;
    image->buffer1 = dst_data;
    image->red_mask = 0xff0000;
    image->green_mask = 0x00ff00;
    image->blue_mask = 0x0000ff;
    image->palette_size = 0;
    image->palette = NULL;

    return D3DRM_OK;
}