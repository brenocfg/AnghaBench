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
typedef  unsigned int uint8_t ;
struct tas571x_private {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct tas571x_private* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_send (struct i2c_client*,unsigned int*,unsigned int) ; 
 unsigned int tas571x_register_size (struct tas571x_private*,unsigned int) ; 

__attribute__((used)) static int tas571x_reg_write(void *context, unsigned int reg,
			     unsigned int value)
{
	struct i2c_client *client = context;
	struct tas571x_private *priv = i2c_get_clientdata(client);
	unsigned int i, size;
	uint8_t buf[5];
	int ret;

	size = tas571x_register_size(priv, reg);
	buf[0] = reg;

	for (i = size; i >= 1; --i) {
		buf[i] = value;
		value >>= 8;
	}

	ret = i2c_master_send(client, buf, size + 1);
	if (ret == size + 1)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}