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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RX8025_ADJ_RESOLUTION ; 
 int /*<<< orphan*/  RX8025_REG_DIGOFF ; 
 int rx8025_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int rx8025_get_clock_adjust(struct device *dev, int *adj)
{
	struct i2c_client *client = to_i2c_client(dev);
	int digoff;

	digoff = rx8025_read_reg(client, RX8025_REG_DIGOFF);
	if (digoff < 0)
		return digoff;

	*adj = digoff >= 64 ? digoff - 128 : digoff;
	if (*adj > 0)
		(*adj)--;
	*adj *= -RX8025_ADJ_RESOLUTION;

	return 0;
}