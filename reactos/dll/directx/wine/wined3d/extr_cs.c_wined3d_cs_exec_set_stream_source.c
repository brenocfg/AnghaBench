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
struct wined3d_stream_state {int /*<<< orphan*/  stride; int /*<<< orphan*/  offset; struct wined3d_buffer* buffer; } ;
struct wined3d_cs_set_stream_source {size_t stream_idx; struct wined3d_buffer* buffer; int /*<<< orphan*/  stride; int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {struct wined3d_stream_state* streams; } ;
struct wined3d_cs {int /*<<< orphan*/  device; TYPE_1__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  bind_count; } ;
struct wined3d_buffer {TYPE_2__ resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATE_STREAMSRC ; 
 int /*<<< orphan*/  device_invalidate_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_set_stream_source(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_stream_source *op = data;
    struct wined3d_stream_state *stream;
    struct wined3d_buffer *prev;

    stream = &cs->state.streams[op->stream_idx];
    prev = stream->buffer;
    stream->buffer = op->buffer;
    stream->offset = op->offset;
    stream->stride = op->stride;

    if (op->buffer)
        InterlockedIncrement(&op->buffer->resource.bind_count);
    if (prev)
        InterlockedDecrement(&prev->resource.bind_count);

    device_invalidate_state(cs->device, STATE_STREAMSRC);
}