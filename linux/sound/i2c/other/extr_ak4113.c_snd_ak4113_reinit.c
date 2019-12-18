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
struct ak4113 {int /*<<< orphan*/  work; int /*<<< orphan*/  wq_processing; int /*<<< orphan*/  reinit_mutex; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ak4113_init_regs (struct ak4113*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

void snd_ak4113_reinit(struct ak4113 *chip)
{
	if (atomic_inc_return(&chip->wq_processing) == 1)
		cancel_delayed_work_sync(&chip->work);
	mutex_lock(&chip->reinit_mutex);
	ak4113_init_regs(chip);
	mutex_unlock(&chip->reinit_mutex);
	/* bring up statistics / event queing */
	if (atomic_dec_and_test(&chip->wq_processing))
		schedule_delayed_work(&chip->work, HZ / 10);
}