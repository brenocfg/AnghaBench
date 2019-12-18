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
struct TYPE_2__ {unsigned int numerator; unsigned int denominator; } ;
struct wined3d_format {int* flags; unsigned int block_width; unsigned int block_height; unsigned int block_byte_count; unsigned int byte_count; TYPE_1__ height_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int) ; 
 int WINED3DFMT_FLAG_BLOCKS ; 
 int WINED3DFMT_FLAG_HEIGHT_SCALE ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 

void wined3d_format_calculate_pitch(const struct wined3d_format *format, unsigned int alignment,
        unsigned int width, unsigned int height, unsigned int *row_pitch, unsigned int *slice_pitch)
{
    /* For block based formats, pitch means the amount of bytes to the next
     * row of blocks rather than the next row of pixels. */
    if (format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_BLOCKS)
    {
        unsigned int row_block_count = (width + format->block_width - 1) / format->block_width;
        unsigned int slice_block_count = (height + format->block_height - 1) / format->block_height;
        *row_pitch = row_block_count * format->block_byte_count;
        *row_pitch = (*row_pitch + alignment - 1) & ~(alignment - 1);
        *slice_pitch = *row_pitch * slice_block_count;
    }
    else
    {
        *row_pitch = format->byte_count * width;  /* Bytes / row */
        *row_pitch = (*row_pitch + alignment - 1) & ~(alignment - 1);
        *slice_pitch = *row_pitch * height;
    }

    if (format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_HEIGHT_SCALE)
    {
        /* The D3D format requirements make sure that the resulting format is an integer again */
        *slice_pitch *= format->height_scale.numerator;
        *slice_pitch /= format->height_scale.denominator;
    }

    TRACE("Returning row pitch %u, slice pitch %u.\n", *row_pitch, *slice_pitch);
}