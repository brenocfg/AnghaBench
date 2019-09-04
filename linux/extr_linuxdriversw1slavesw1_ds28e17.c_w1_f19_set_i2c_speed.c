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
typedef  int /*<<< orphan*/  u8 ;
struct w1_slave {TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int __w1_f19_set_i2c_speed (struct w1_slave*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int w1_f19_set_i2c_speed(struct w1_slave *sl, u8 speed)
{
	int result;

	/* Start onewire transaction. */
	mutex_lock(&sl->master->bus_mutex);

	/* Set I2C speed on DS28E17. */
	result = __w1_f19_set_i2c_speed(sl, speed);

	/* End onewire transaction. */
	mutex_unlock(&sl->master->bus_mutex);

	return result;
}