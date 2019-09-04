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
struct mpv_handle {size_t num_events; size_t reserved_events; size_t max_events; size_t first_event; unsigned long long event_mask; struct mpv_event* events; } ;
struct mpv_event {unsigned long long event_id; } ;

/* Variables and functions */
 unsigned long long MPV_EVENT_SHUTDOWN ; 
 int /*<<< orphan*/  dup_event_data (struct mpv_event*) ; 
 int /*<<< orphan*/  wakeup_client (struct mpv_handle*) ; 

__attribute__((used)) static int append_event(struct mpv_handle *ctx, struct mpv_event event, bool copy)
{
    if (ctx->num_events + ctx->reserved_events >= ctx->max_events)
        return -1;
    if (copy)
        dup_event_data(&event);
    ctx->events[(ctx->first_event + ctx->num_events) % ctx->max_events] = event;
    ctx->num_events++;
    wakeup_client(ctx);
    if (event.event_id == MPV_EVENT_SHUTDOWN)
        ctx->event_mask &= ctx->event_mask & ~(1ULL << MPV_EVENT_SHUTDOWN);
    return 0;
}