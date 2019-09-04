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
struct vo_internal {int vsync_interval; int /*<<< orphan*/  lock; } ;
struct vo {struct vo_internal* in; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int64_t vo_get_vsync_interval(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    pthread_mutex_lock(&in->lock);
    int64_t res = vo->in->vsync_interval > 1 ? vo->in->vsync_interval : -1;
    pthread_mutex_unlock(&in->lock);
    return res;
}