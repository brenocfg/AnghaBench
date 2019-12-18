#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int start_idx; unsigned int count; } ;
struct TYPE_6__ {TYPE_2__ buffer; } ;
struct wined3d_view_desc {scalar_t__ format_id; TYPE_3__ u; } ;
struct wined3d_format {unsigned int byte_count; } ;
struct TYPE_4__ {unsigned int structure_byte_stride; } ;
struct wined3d_buffer {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ WINED3DFMT_UNKNOWN ; 

__attribute__((used)) static void get_buffer_view_range(const struct wined3d_buffer *buffer,
        const struct wined3d_view_desc *desc, const struct wined3d_format *view_format,
        unsigned int *offset, unsigned int *size)
{
    if (desc->format_id == WINED3DFMT_UNKNOWN)
    {
        *offset = desc->u.buffer.start_idx * buffer->desc.structure_byte_stride;
        *size = desc->u.buffer.count * buffer->desc.structure_byte_stride;
    }
    else
    {
        *offset = desc->u.buffer.start_idx * view_format->byte_count;
        *size = desc->u.buffer.count * view_format->byte_count;
    }
}