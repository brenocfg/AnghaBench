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
struct vo {struct priv* priv; } ;
struct timespec {int dummy; } ;
struct priv {scalar_t__ vsync_counter; int /*<<< orphan*/  display_mutex; int /*<<< orphan*/  display_cond; int /*<<< orphan*/  reload_display; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 struct timespec mp_rel_time_to_timespec (double) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_next_vsync(struct vo *vo)
{
    struct priv *p = vo->priv;
    pthread_mutex_lock(&p->display_mutex);
    struct timespec end = mp_rel_time_to_timespec(0.050);
    int64_t old = p->vsync_counter;
    while (old == p->vsync_counter && !p->reload_display) {
        if (pthread_cond_timedwait(&p->display_cond, &p->display_mutex, &end))
            break;
    }
    pthread_mutex_unlock(&p->display_mutex);
}