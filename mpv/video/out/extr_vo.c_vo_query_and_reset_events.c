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
struct vo_internal {int queued_events; int /*<<< orphan*/  lock; } ;
struct vo {struct vo_internal* in; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int vo_query_and_reset_events(struct vo *vo, int events)
{
    struct vo_internal *in = vo->in;
    pthread_mutex_lock(&in->lock);
    int r = in->queued_events & events;
    in->queued_events &= ~(unsigned)r;
    pthread_mutex_unlock(&in->lock);
    return r;
}