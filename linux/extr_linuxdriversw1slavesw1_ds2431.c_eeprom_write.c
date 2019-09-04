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
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  W1_F2D_EEPROM_SIZE ; 
 int W1_F2D_SCRATCH_MASK ; 
 int W1_F2D_SCRATCH_SIZE ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t w1_f2d_fix_count (int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ w1_f2d_readblock (struct w1_slave*,int,int,char*) ; 
 scalar_t__ w1_f2d_write (struct w1_slave*,int,int,char*) ; 

__attribute__((used)) static ssize_t eeprom_write(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr, char *buf,
			    loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int addr, len;
	int copy;

	count = w1_f2d_fix_count(off, count, W1_F2D_EEPROM_SIZE);
	if (count == 0)
		return 0;

	mutex_lock(&sl->master->bus_mutex);

	/* Can only write data in blocks of the size of the scratchpad */
	addr = off;
	len = count;
	while (len > 0) {

		/* if len too short or addr not aligned */
		if (len < W1_F2D_SCRATCH_SIZE || addr & W1_F2D_SCRATCH_MASK) {
			char tmp[W1_F2D_SCRATCH_SIZE];

			/* read the block and update the parts to be written */
			if (w1_f2d_readblock(sl, addr & ~W1_F2D_SCRATCH_MASK,
					W1_F2D_SCRATCH_SIZE, tmp)) {
				count = -EIO;
				goto out_up;
			}

			/* copy at most to the boundary of the PAGE or len */
			copy = W1_F2D_SCRATCH_SIZE -
				(addr & W1_F2D_SCRATCH_MASK);

			if (copy > len)
				copy = len;

			memcpy(&tmp[addr & W1_F2D_SCRATCH_MASK], buf, copy);
			if (w1_f2d_write(sl, addr & ~W1_F2D_SCRATCH_MASK,
					W1_F2D_SCRATCH_SIZE, tmp) < 0) {
				count = -EIO;
				goto out_up;
			}
		} else {

			copy = W1_F2D_SCRATCH_SIZE;
			if (w1_f2d_write(sl, addr, copy, buf) < 0) {
				count = -EIO;
				goto out_up;
			}
		}
		buf += copy;
		addr += copy;
		len -= copy;
	}

out_up:
	mutex_unlock(&sl->master->bus_mutex);

	return count;
}