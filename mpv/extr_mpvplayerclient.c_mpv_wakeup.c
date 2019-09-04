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
struct TYPE_4__ {int queued_wakeup; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_client (TYPE_1__*) ; 

void mpv_wakeup(mpv_handle *ctx)
{
    pthread_mutex_lock(&ctx->lock);
    ctx->queued_wakeup = true;
    wakeup_client(ctx);
    pthread_mutex_unlock(&ctx->lock);
}