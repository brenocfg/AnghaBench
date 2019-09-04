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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct da9150_fg {int /*<<< orphan*/  dev; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_QIF_SYNC ; 
 int /*<<< orphan*/  DA9150_QIF_SYNC_RETRIES ; 
 int /*<<< orphan*/  DA9150_QIF_SYNC_SIZE ; 
 int DA9150_QIF_SYNC_TIMEOUT ; 
 scalar_t__ da9150_fg_read_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_write_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void da9150_fg_write_attr_sync(struct da9150_fg *fg, u8 code, u8 size,
				      u32 val)
{
	int i = 0;
	u32 res = 0, sync_val;

	mutex_lock(&fg->io_lock);

	/* Check if QIF sync already requested */
	res = da9150_fg_read_attr(fg, DA9150_QIF_SYNC,
				  DA9150_QIF_SYNC_SIZE);

	/* Wait for an existing sync to complete */
	while ((res == 0) && (i++ < DA9150_QIF_SYNC_RETRIES)) {
		usleep_range(DA9150_QIF_SYNC_TIMEOUT,
			     DA9150_QIF_SYNC_TIMEOUT * 2);
		res = da9150_fg_read_attr(fg, DA9150_QIF_SYNC,
					  DA9150_QIF_SYNC_SIZE);
	}

	if (res == 0) {
		dev_err(fg->dev, "Timeout waiting for existing QIF sync!\n");
		mutex_unlock(&fg->io_lock);
		return;
	}

	/* Write value for QIF code */
	da9150_fg_write_attr(fg, code, size, val);

	/* Wait for write acknowledgment */
	i = 0;
	sync_val = res;
	while ((res == sync_val) && (i++ < DA9150_QIF_SYNC_RETRIES)) {
		usleep_range(DA9150_QIF_SYNC_TIMEOUT,
			     DA9150_QIF_SYNC_TIMEOUT * 2);
		res = da9150_fg_read_attr(fg, DA9150_QIF_SYNC,
					  DA9150_QIF_SYNC_SIZE);
	}

	mutex_unlock(&fg->io_lock);

	/* Check write was actually successful */
	if (res != (sync_val + 1))
		dev_err(fg->dev, "Error performing QIF sync write for code %d\n",
			code);
}