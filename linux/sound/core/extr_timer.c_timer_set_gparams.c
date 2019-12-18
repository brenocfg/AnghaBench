#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_timer_gparams {int /*<<< orphan*/  period_den; int /*<<< orphan*/  period_num; int /*<<< orphan*/  tid; } ;
struct TYPE_2__ {int (* set_period ) (struct snd_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct snd_timer {TYPE_1__ hw; int /*<<< orphan*/  open_list_head; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 struct snd_timer* snd_timer_find (int /*<<< orphan*/ *) ; 
 int stub1 (struct snd_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer_set_gparams(struct snd_timer_gparams *gparams)
{
	struct snd_timer *t;
	int err;

	mutex_lock(&register_mutex);
	t = snd_timer_find(&gparams->tid);
	if (!t) {
		err = -ENODEV;
		goto _error;
	}
	if (!list_empty(&t->open_list_head)) {
		err = -EBUSY;
		goto _error;
	}
	if (!t->hw.set_period) {
		err = -ENOSYS;
		goto _error;
	}
	err = t->hw.set_period(t, gparams->period_num, gparams->period_den);
_error:
	mutex_unlock(&register_mutex);
	return err;
}