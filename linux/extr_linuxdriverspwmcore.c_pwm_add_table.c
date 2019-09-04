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
struct pwm_lookup {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_lookup_list ; 
 int /*<<< orphan*/  pwm_lookup_lock ; 

void pwm_add_table(struct pwm_lookup *table, size_t num)
{
	mutex_lock(&pwm_lookup_lock);

	while (num--) {
		list_add_tail(&table->list, &pwm_lookup_list);
		table++;
	}

	mutex_unlock(&pwm_lookup_lock);
}