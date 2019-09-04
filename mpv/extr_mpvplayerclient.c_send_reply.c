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
typedef  int /*<<< orphan*/  uint64_t ;
struct mpv_handle {scalar_t__ reserved_events; int /*<<< orphan*/  lock; } ;
struct mpv_event {int /*<<< orphan*/  reply_userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ append_event (struct mpv_handle*,struct mpv_event,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_reply(struct mpv_handle *ctx, uint64_t userdata,
                       struct mpv_event *event)
{
    event->reply_userdata = userdata;
    pthread_mutex_lock(&ctx->lock);
    // If this fails, reserve_reply() probably wasn't called.
    assert(ctx->reserved_events > 0);
    ctx->reserved_events--;
    if (append_event(ctx, *event, false) < 0)
        abort(); // not reached
    pthread_mutex_unlock(&ctx->lock);
}