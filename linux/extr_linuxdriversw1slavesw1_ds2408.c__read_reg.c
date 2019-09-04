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
typedef  scalar_t__ u8 ;
struct w1_slave {int /*<<< orphan*/  dev; TYPE_1__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ W1_F29_FUNC_READ_PIO_REGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned char w1_read_8 (TYPE_1__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,scalar_t__*,int) ; 

__attribute__((used)) static int _read_reg(struct w1_slave *sl, u8 address, unsigned char* buf)
{
	u8 wrbuf[3];
	dev_dbg(&sl->dev,
			"Reading with slave: %p, reg addr: %0#4x, buff addr: %p",
			sl, (unsigned int)address, buf);

	if (!buf)
		return -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

	if (w1_reset_select_slave(sl)) {
		mutex_unlock(&sl->master->bus_mutex);
		return -EIO;
	}

	wrbuf[0] = W1_F29_FUNC_READ_PIO_REGS;
	wrbuf[1] = address;
	wrbuf[2] = 0;
	w1_write_block(sl->master, wrbuf, 3);
	*buf = w1_read_8(sl->master);

	mutex_unlock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex unlocked");
	return 1;
}