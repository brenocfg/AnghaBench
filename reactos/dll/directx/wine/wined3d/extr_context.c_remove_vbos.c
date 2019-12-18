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
struct TYPE_4__ {int /*<<< orphan*/  addr; scalar_t__ buffer_object; } ;
struct wined3d_stream_info_element {size_t stream_idx; TYPE_2__ data; } ;
struct wined3d_stream_info {unsigned int use_map; struct wined3d_stream_info_element* elements; } ;
struct wined3d_state {TYPE_1__* streams; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_buffer {int dummy; } ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {struct wined3d_buffer* buffer; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct wined3d_stream_info_element*) ; 
 scalar_t__ wined3d_buffer_load_sysmem (struct wined3d_buffer*,struct wined3d_context*) ; 

__attribute__((used)) static void remove_vbos(struct wined3d_context *context,
        const struct wined3d_state *state, struct wined3d_stream_info *s)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->elements); ++i)
    {
        struct wined3d_stream_info_element *e;

        if (!(s->use_map & (1u << i)))
            continue;

        e = &s->elements[i];
        if (e->data.buffer_object)
        {
            struct wined3d_buffer *vb = state->streams[e->stream_idx].buffer;
            e->data.buffer_object = 0;
            e->data.addr += (ULONG_PTR)wined3d_buffer_load_sysmem(vb, context);
        }
    }
}