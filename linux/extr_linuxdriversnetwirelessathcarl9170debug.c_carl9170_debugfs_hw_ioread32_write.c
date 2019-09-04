#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ring_tail; TYPE_1__* ring; } ;
struct ar9170 {TYPE_2__ debug; } ;
typedef  int ssize_t ;
struct TYPE_3__ {unsigned int reg; unsigned int value; } ;

/* Variables and functions */
 size_t CARL9170_DEBUG_RING_SIZE ; 
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int carl9170_read_reg (struct ar9170*,unsigned int,unsigned int*) ; 
 int sscanf (char const*,char*,unsigned int*,int*) ; 

__attribute__((used)) static ssize_t carl9170_debugfs_hw_ioread32_write(struct ar9170 *ar,
	const char *buf, size_t count)
{
	int err = 0, i, n = 0, max_len = 32, res;
	unsigned int reg, tmp;

	if (!count)
		return 0;

	if (count > max_len)
		return -E2BIG;

	res = sscanf(buf, "0x%X %d", &reg, &n);
	if (res < 1) {
		err = -EINVAL;
		goto out;
	}

	if (res == 1)
		n = 1;

	if (n > 15) {
		err = -EMSGSIZE;
		goto out;
	}

	if ((reg >= 0x280000) || ((reg + (n << 2)) >= 0x280000)) {
		err = -EADDRNOTAVAIL;
		goto out;
	}

	if (reg & 3) {
		err = -EINVAL;
		goto out;
	}

	for (i = 0; i < n; i++) {
		err = carl9170_read_reg(ar, reg + (i << 2), &tmp);
		if (err)
			goto out;

		ar->debug.ring[ar->debug.ring_tail].reg = reg + (i << 2);
		ar->debug.ring[ar->debug.ring_tail].value = tmp;
		ar->debug.ring_tail++;
		ar->debug.ring_tail %= CARL9170_DEBUG_RING_SIZE;
	}

out:
	return err ? err : count;
}