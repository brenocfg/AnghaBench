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
struct TYPE_2__ {int (* start ) () ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_setup ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ oprofile_ops ; 
 int /*<<< orphan*/  oprofile_reset_stats () ; 
 int oprofile_started ; 
 int /*<<< orphan*/  start_mutex ; 
 int /*<<< orphan*/  start_switch_worker () ; 
 int stub1 () ; 

int oprofile_start(void)
{
	int err = -EINVAL;

	mutex_lock(&start_mutex);

	if (!is_setup)
		goto out;

	err = 0;

	if (oprofile_started)
		goto out;

	oprofile_reset_stats();

	if ((err = oprofile_ops.start()))
		goto out;

	start_switch_worker();

	oprofile_started = 1;
out:
	mutex_unlock(&start_mutex);
	return err;
}