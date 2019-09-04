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
typedef  int u8 ;
struct w1_slave {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int W1_DS2438_COPY_SCRATCH ; 
 int W1_DS2438_READ_SCRATCH ; 
 int W1_DS2438_RECALL_MEMORY ; 
 unsigned int W1_DS2438_RETRIES ; 
 int W1_DS2438_WRITE_SCRATCH ; 
 int w1_read_8 (int /*<<< orphan*/ ) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int w1_ds2438_change_config_bit(struct w1_slave *sl, u8 mask, u8 value)
{
	unsigned int retries = W1_DS2438_RETRIES;
	u8 w1_buf[3];
	u8 status;
	int perform_write = 0;

	while (retries--) {
		if (w1_reset_select_slave(sl))
			continue;
		w1_buf[0] = W1_DS2438_RECALL_MEMORY;
		w1_buf[1] = 0x00;
		w1_write_block(sl->master, w1_buf, 2);

		if (w1_reset_select_slave(sl))
			continue;
		w1_buf[0] = W1_DS2438_READ_SCRATCH;
		w1_buf[1] = 0x00;
		w1_write_block(sl->master, w1_buf, 2);

		/* reading one byte of result */
		status = w1_read_8(sl->master);

		/* if bit0=1, set a value to a mask for easy compare */
		if (value)
			value = mask;

		if ((status & mask) == value)
			return 0;	/* already set as requested */
		else {
			/* changing bit */
			status ^= mask;
			perform_write = 1;
		}
		break;
	}

	if (perform_write) {
		retries = W1_DS2438_RETRIES;
		while (retries--) {
			if (w1_reset_select_slave(sl))
				continue;
			w1_buf[0] = W1_DS2438_WRITE_SCRATCH;
			w1_buf[1] = 0x00;
			w1_buf[2] = status;
			w1_write_block(sl->master, w1_buf, 3);

			if (w1_reset_select_slave(sl))
				continue;
			w1_buf[0] = W1_DS2438_COPY_SCRATCH;
			w1_buf[1] = 0x00;
			w1_write_block(sl->master, w1_buf, 2);

			return 0;
		}
	}
	return -1;
}