#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct w1_slave {int /*<<< orphan*/  dev; TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 scalar_t__ W1_F29_FUNC_CHANN_ACCESS_WRITE ; 
 unsigned int W1_F29_RETRIES ; 
 scalar_t__ W1_F29_SUCCESS_CONFIRM_BYTE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_read_8 (TYPE_1__*) ; 
 scalar_t__ w1_reset_resume_command (TYPE_1__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,scalar_t__*,int) ; 

__attribute__((used)) static ssize_t output_write(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr, char *buf,
			    loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 w1_buf[3];
	u8 readBack;
	unsigned int retries = W1_F29_RETRIES;

	if (count != 1 || off != 0)
		return -EFAULT;

	dev_dbg(&sl->dev, "locking mutex for write_output");
	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

	if (w1_reset_select_slave(sl))
		goto error;

	while (retries--) {
		w1_buf[0] = W1_F29_FUNC_CHANN_ACCESS_WRITE;
		w1_buf[1] = *buf;
		w1_buf[2] = ~(*buf);
		w1_write_block(sl->master, w1_buf, 3);

		readBack = w1_read_8(sl->master);

		if (readBack != W1_F29_SUCCESS_CONFIRM_BYTE) {
			if (w1_reset_resume_command(sl->master))
				goto error;
			/* try again, the slave is ready for a command */
			continue;
		}

#ifdef CONFIG_W1_SLAVE_DS2408_READBACK
		/* here the master could read another byte which
		   would be the PIO reg (the actual pin logic state)
		   since in this driver we don't know which pins are
		   in and outs, there's no value to read the state and
		   compare. with (*buf) so end this command abruptly: */
		if (w1_reset_resume_command(sl->master))
			goto error;

		/* go read back the output latches */
		/* (the direct effect of the write above) */
		w1_buf[0] = W1_F29_FUNC_READ_PIO_REGS;
		w1_buf[1] = W1_F29_REG_OUTPUT_LATCH_STATE;
		w1_buf[2] = 0;
		w1_write_block(sl->master, w1_buf, 3);
		/* read the result of the READ_PIO_REGS command */
		if (w1_read_8(sl->master) == *buf)
#endif
		{
			/* success! */
			mutex_unlock(&sl->master->bus_mutex);
			dev_dbg(&sl->dev,
				"mutex unlocked, retries:%d", retries);
			return 1;
		}
	}
error:
	mutex_unlock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex unlocked in error, retries:%d", retries);

	return -EIO;
}