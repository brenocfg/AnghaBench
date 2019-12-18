#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sd_times {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct dec_sub {double last_vo_pts; int /*<<< orphan*/  lock; TYPE_2__* sd; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {struct sd_times (* get_times ) (TYPE_2__*,double) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 double pts_to_subtitle (struct dec_sub*,double) ; 
 struct sd_times stub1 (TYPE_2__*,double) ; 
 int /*<<< orphan*/  update_segment (struct dec_sub*) ; 

struct sd_times sub_get_times(struct dec_sub *sub, double pts)
{
    pthread_mutex_lock(&sub->lock);
    struct sd_times res = { .start = MP_NOPTS_VALUE, .end = MP_NOPTS_VALUE };

    pts = pts_to_subtitle(sub, pts);

    sub->last_vo_pts = pts;
    update_segment(sub);

    if (sub->sd->driver->get_times)
        res = sub->sd->driver->get_times(sub->sd, pts);

    pthread_mutex_unlock(&sub->lock);
    return res;
}