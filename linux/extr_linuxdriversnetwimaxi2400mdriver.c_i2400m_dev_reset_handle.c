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
struct i2400m {char const* reset_reason; int /*<<< orphan*/  reset_ws; } ;

/* Variables and functions */
 int schedule_work (int /*<<< orphan*/ *) ; 

int i2400m_dev_reset_handle(struct i2400m *i2400m, const char *reason)
{
	i2400m->reset_reason = reason;
	return schedule_work(&i2400m->reset_ws);
}