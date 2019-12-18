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
struct pmac_keywest {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int ENXIO ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int send_init_client(struct pmac_keywest *i2c, unsigned int *regs)
{
	while (*regs > 0) {
		int err, count = 10;
		do {
			err = i2c_smbus_write_byte_data(i2c->client,
							regs[0], regs[1]);
			if (err >= 0)
				break;
			DBG("(W) i2c error %d\n", err);
			mdelay(10);
		} while (count--);
		if (err < 0)
			return -ENXIO;
		regs += 2;
	}
	return 0;
}