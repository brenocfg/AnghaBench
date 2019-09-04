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
typedef  int uint64_t ;
struct mpv_handle {int property_event_masks; int event_mask; int choked; int /*<<< orphan*/  lock; } ;
struct mpv_event {unsigned long long event_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mpv_handle*,char*) ; 
 int append_event (struct mpv_handle*,struct mpv_event,int) ; 
 int /*<<< orphan*/  notify_property_events (struct mpv_handle*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_event(struct mpv_handle *ctx, struct mpv_event *event, bool copy)
{
    pthread_mutex_lock(&ctx->lock);
    uint64_t mask = 1ULL << event->event_id;
    if (ctx->property_event_masks & mask)
        notify_property_events(ctx, mask);
    int r;
    if (!(ctx->event_mask & mask)) {
        r = 0;
    } else if (ctx->choked) {
        r = -1;
    } else {
        r = append_event(ctx, *event, copy);
        if (r < 0) {
            MP_ERR(ctx, "Too many events queued.\n");
            ctx->choked = true;
        }
    }
    pthread_mutex_unlock(&ctx->lock);
    return r;
}