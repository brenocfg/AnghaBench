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
struct volume {int depth; int height; int width; } ;
struct vec4 {float w; } ;
struct pixel_format_desc {int bytes_per_pixel; scalar_t__ type; int /*<<< orphan*/  (* from_rgba ) (struct vec4*,struct vec4*) ;int /*<<< orphan*/  (* to_rgba ) (struct vec4*,struct vec4*,int /*<<< orphan*/  const*) ;} ;
struct argb_conversion_info {scalar_t__* destmask; } ;
typedef  int /*<<< orphan*/  channels ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ D3DCOLOR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_A8R8G8B8 ; 
 int /*<<< orphan*/  ZeroMemory (scalar_t__*,int) ; 
 int /*<<< orphan*/  format_from_vec4 (struct pixel_format_desc const*,struct vec4*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_to_vec4 (struct pixel_format_desc const*,int /*<<< orphan*/  const*,struct vec4*) ; 
 struct pixel_format_desc* get_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relevant_argb_components (struct argb_conversion_info*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  init_argb_conversion_info (struct pixel_format_desc const*,struct pixel_format_desc const*,struct argb_conversion_info*) ; 
 scalar_t__ make_argb_color (struct argb_conversion_info*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub1 (struct vec4*,struct vec4*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (struct vec4*,struct vec4*) ; 

void point_filter_argb_pixels(const BYTE *src, UINT src_row_pitch, UINT src_slice_pitch, const struct volume *src_size,
        const struct pixel_format_desc *src_format, BYTE *dst, UINT dst_row_pitch, UINT dst_slice_pitch,
        const struct volume *dst_size, const struct pixel_format_desc *dst_format, D3DCOLOR color_key,
        const PALETTEENTRY *palette)
{
    struct argb_conversion_info conv_info, ck_conv_info;
    const struct pixel_format_desc *ck_format = NULL;
    DWORD channels[4];
    UINT x, y, z;

    ZeroMemory(channels, sizeof(channels));
    init_argb_conversion_info(src_format, dst_format, &conv_info);

    if (color_key)
    {
        /* Color keys are always represented in D3DFMT_A8R8G8B8 format. */
        ck_format = get_format_info(D3DFMT_A8R8G8B8);
        init_argb_conversion_info(src_format, ck_format, &ck_conv_info);
    }

    for (z = 0; z < dst_size->depth; z++)
    {
        BYTE *dst_slice_ptr = dst + z * dst_slice_pitch;
        const BYTE *src_slice_ptr = src + src_slice_pitch * (z * src_size->depth / dst_size->depth);

        for (y = 0; y < dst_size->height; y++)
        {
            BYTE *dst_ptr = dst_slice_ptr + y * dst_row_pitch;
            const BYTE *src_row_ptr = src_slice_ptr + src_row_pitch * (y * src_size->height / dst_size->height);

            for (x = 0; x < dst_size->width; x++)
            {
                const BYTE *src_ptr = src_row_ptr + (x * src_size->width / dst_size->width) * src_format->bytes_per_pixel;

                if (!src_format->to_rgba && !dst_format->from_rgba
                        && src_format->type == dst_format->type
                        && src_format->bytes_per_pixel <= 4 && dst_format->bytes_per_pixel <= 4)
                {
                    DWORD val;

                    get_relevant_argb_components(&conv_info, src_ptr, channels);
                    val = make_argb_color(&conv_info, channels);

                    if (color_key)
                    {
                        DWORD ck_pixel;

                        get_relevant_argb_components(&ck_conv_info, src_ptr, channels);
                        ck_pixel = make_argb_color(&ck_conv_info, channels);
                        if (ck_pixel == color_key)
                            val &= ~conv_info.destmask[0];
                    }
                    memcpy(dst_ptr, &val, dst_format->bytes_per_pixel);
                }
                else
                {
                    struct vec4 color, tmp;

                    format_to_vec4(src_format, src_ptr, &color);
                    if (src_format->to_rgba)
                        src_format->to_rgba(&color, &tmp, palette);
                    else
                        tmp = color;

                    if (ck_format)
                    {
                        DWORD ck_pixel;

                        format_from_vec4(ck_format, &tmp, (BYTE *)&ck_pixel);
                        if (ck_pixel == color_key)
                            tmp.w = 0.0f;
                    }

                    if (dst_format->from_rgba)
                        dst_format->from_rgba(&tmp, &color);
                    else
                        color = tmp;

                    format_from_vec4(dst_format, &color, dst_ptr);
                }

                dst_ptr += dst_format->bytes_per_pixel;
            }
        }
    }
}