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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int wm2000_read (struct i2c_client*,unsigned int) ; 

__attribute__((used)) static int wm2000_poll_bit(struct i2c_client *i2c,
			   unsigned int reg, u8 mask)
{
	int timeout = 4000;
	int val;

	val = wm2000_read(i2c, reg);

	while (!(val & mask) && --timeout) {
		msleep(1);
		val = wm2000_read(i2c, reg);
	}

	if (timeout == 0)
		return 0;
	else
		return 1;
}