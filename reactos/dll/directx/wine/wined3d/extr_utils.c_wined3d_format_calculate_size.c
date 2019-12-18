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
struct wined3d_format {scalar_t__ id; int* flags; unsigned int byte_count; } ;
typedef  unsigned int UINT ;

/* Variables and functions */
 int WINED3DFMT_FLAG_BROKEN_PITCH ; 
 scalar_t__ WINED3DFMT_UNKNOWN ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 int /*<<< orphan*/  wined3d_format_calculate_pitch (struct wined3d_format const*,unsigned int,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 

UINT wined3d_format_calculate_size(const struct wined3d_format *format, UINT alignment,
        UINT width, UINT height, UINT depth)
{
    unsigned int row_pitch, slice_pitch;

    if (format->id == WINED3DFMT_UNKNOWN)
        return 0;

    if (format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_BROKEN_PITCH)
        return width * height * depth * format->byte_count;

    wined3d_format_calculate_pitch(format, alignment, width, height, &row_pitch, &slice_pitch);

    return slice_pitch * depth;
}