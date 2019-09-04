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
struct bq2415x_device {int autotimer; int /*<<< orphan*/  work; int /*<<< orphan*/ * timer_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_TIMER_RESET ; 
 int BQ2415X_TIMER_TIMEOUT ; 
 int HZ ; 
 int /*<<< orphan*/  bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq2415x_timer_mutex ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bq2415x_set_autotimer(struct bq2415x_device *bq, int state)
{
	mutex_lock(&bq2415x_timer_mutex);

	if (bq->autotimer == state) {
		mutex_unlock(&bq2415x_timer_mutex);
		return;
	}

	bq->autotimer = state;

	if (state) {
		schedule_delayed_work(&bq->work, BQ2415X_TIMER_TIMEOUT * HZ);
		bq2415x_exec_command(bq, BQ2415X_TIMER_RESET);
		bq->timer_error = NULL;
	} else {
		cancel_delayed_work_sync(&bq->work);
	}

	mutex_unlock(&bq2415x_timer_mutex);
}