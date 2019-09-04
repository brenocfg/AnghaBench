#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct w1_slave {TYPE_1__* master; struct w1_f19_data* family_data; } ;
struct w1_f19_data {int speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  W1_F19_READ_CONFIGURATION ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_read_8 (TYPE_1__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_8 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_f19_get_i2c_speed(struct w1_slave *sl)
{
	struct w1_f19_data *data = sl->family_data;
	int result = -EIO;

	/* Start onewire transaction. */
	mutex_lock(&sl->master->bus_mutex);

	/* Select slave. */
	if (w1_reset_select_slave(sl))
		goto error;

	/* Read slave configuration byte. */
	w1_write_8(sl->master, W1_F19_READ_CONFIGURATION);
	result = w1_read_8(sl->master);
	if (result < 0 || result > 2) {
		result = -EIO;
		goto error;
	}

	/* Update speed in slave specific data. */
	data->speed = result;

error:
	/* End onewire transaction. */
	mutex_unlock(&sl->master->bus_mutex);

	return result;
}