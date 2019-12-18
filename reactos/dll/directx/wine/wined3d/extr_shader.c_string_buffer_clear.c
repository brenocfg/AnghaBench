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
struct wined3d_string_buffer {char* buffer; scalar_t__ content_size; } ;

/* Variables and functions */

void string_buffer_clear(struct wined3d_string_buffer *buffer)
{
    buffer->buffer[0] = '\0';
    buffer->content_size = 0;
}