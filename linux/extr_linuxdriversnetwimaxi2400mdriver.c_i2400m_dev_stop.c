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
struct i2400m {int /*<<< orphan*/  init_mutex; scalar_t__ alive; scalar_t__ updown; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i2400m_dev_stop (struct i2400m*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static
void i2400m_dev_stop(struct i2400m *i2400m)
{
	mutex_lock(&i2400m->init_mutex);
	if (i2400m->updown) {
		__i2400m_dev_stop(i2400m);
		i2400m->updown = 0;
		i2400m->alive = 0;
		wmb();	/* see i2400m->updown and i2400m->alive's doc */
	}
	mutex_unlock(&i2400m->init_mutex);
}