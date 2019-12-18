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
struct wined3d_string_buffer_list {int /*<<< orphan*/  list; } ;
struct wined3d_string_buffer {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void string_buffer_release(struct wined3d_string_buffer_list *list, struct wined3d_string_buffer *buffer)
{
    if (!buffer)
        return;
    list_add_head(&list->list, &buffer->entry);
}