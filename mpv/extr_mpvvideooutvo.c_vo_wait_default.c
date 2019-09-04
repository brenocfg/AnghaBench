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
struct vo_internal {int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  need_wakeup; } ;
struct vo {struct vo_internal* in; } ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 struct timespec mp_time_us_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void vo_wait_default(struct vo *vo, int64_t until_time)
{
    struct vo_internal *in = vo->in;

    pthread_mutex_lock(&in->lock);
    if (!in->need_wakeup) {
        struct timespec ts = mp_time_us_to_timespec(until_time);
        pthread_cond_timedwait(&in->wakeup, &in->lock, &ts);
    }
    pthread_mutex_unlock(&in->lock);
}