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
struct i2400m {int /*<<< orphan*/  error_recovery; int /*<<< orphan*/  recovery_ws; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void i2400m_error_recovery(struct i2400m *i2400m)
{
	if (atomic_add_return(1, &i2400m->error_recovery) == 1)
		schedule_work(&i2400m->recovery_ws);
	else
		atomic_dec(&i2400m->error_recovery);
}