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
struct timespec {int dummy; } ;
struct mpv_handle {int need_wakeup; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup_lock; int /*<<< orphan*/  wakeup; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 struct timespec mp_time_us_to_timespec (int /*<<< orphan*/ ) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wait_wakeup(struct mpv_handle *ctx, int64_t end)
{
    int r = 0;
    pthread_mutex_unlock(&ctx->lock);
    pthread_mutex_lock(&ctx->wakeup_lock);
    if (!ctx->need_wakeup) {
        struct timespec ts = mp_time_us_to_timespec(end);
        r = pthread_cond_timedwait(&ctx->wakeup, &ctx->wakeup_lock, &ts);
    }
    if (r == 0)
        ctx->need_wakeup = false;
    pthread_mutex_unlock(&ctx->wakeup_lock);
    pthread_mutex_lock(&ctx->lock);
    return r;
}