#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_gl_info {int dummy; } ;
struct wined3d_format {int /*<<< orphan*/  block_byte_count; int /*<<< orphan*/  block_height; int /*<<< orphan*/  block_width; } ;
struct TYPE_3__ {int /*<<< orphan*/  verify; int /*<<< orphan*/  block_byte_count; int /*<<< orphan*/  block_height; int /*<<< orphan*/  block_width; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3DFMT_FLAG_BLOCKS ; 
 int /*<<< orphan*/  WINED3DFMT_FLAG_BLOCKS_NO_VERIFY ; 
 TYPE_1__* format_block_info ; 
 int /*<<< orphan*/  format_set_flag (struct wined3d_format*,int /*<<< orphan*/ ) ; 
 struct wined3d_format* get_format_internal (struct wined3d_gl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL init_format_block_info(struct wined3d_gl_info *gl_info)
{
    struct wined3d_format *format;
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(format_block_info); ++i)
    {
        if (!(format = get_format_internal(gl_info, format_block_info[i].id)))
            return FALSE;

        format->block_width = format_block_info[i].block_width;
        format->block_height = format_block_info[i].block_height;
        format->block_byte_count = format_block_info[i].block_byte_count;
        format_set_flag(format, WINED3DFMT_FLAG_BLOCKS);
        if (!format_block_info[i].verify)
            format_set_flag(format, WINED3DFMT_FLAG_BLOCKS_NO_VERIFY);
    }

    return TRUE;
}