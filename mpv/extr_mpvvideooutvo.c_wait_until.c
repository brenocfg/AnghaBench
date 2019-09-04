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
struct vo_internal {int queued_events; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; } ;
struct vo {struct vo_internal* in; } ;
struct timespec {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int VO_EVENT_LIVE_RESIZING ; 
 scalar_t__ mp_time_us () ; 
 struct timespec mp_time_us_to_timespec (scalar_t__) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_until(struct vo *vo, int64_t target)
{
    struct vo_internal *in = vo->in;
    struct timespec ts = mp_time_us_to_timespec(target);
    pthread_mutex_lock(&in->lock);
    while (target > mp_time_us()) {
        if (in->queued_events & VO_EVENT_LIVE_RESIZING)
            break;
        if (pthread_cond_timedwait(&in->wakeup, &in->lock, &ts))
            break;
    }
    pthread_mutex_unlock(&in->lock);
}