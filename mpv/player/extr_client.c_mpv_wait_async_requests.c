#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ async_counter; scalar_t__ reserved_events; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_wakeup (TYPE_1__*,int /*<<< orphan*/ ) ; 

void mpv_wait_async_requests(mpv_handle *ctx)
{
    pthread_mutex_lock(&ctx->lock);
    while (ctx->reserved_events || ctx->async_counter)
        wait_wakeup(ctx, INT64_MAX);
    pthread_mutex_unlock(&ctx->lock);
}