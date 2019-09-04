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
typedef  int u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int,int,int*) ; 

__attribute__((used)) static int ds1374_read_rtc(struct i2c_client *client, u32 *time,
			   int reg, int nbytes)
{
	u8 buf[4];
	int ret;
	int i;

	if (WARN_ON(nbytes > 4))
		return -EINVAL;

	ret = i2c_smbus_read_i2c_block_data(client, reg, nbytes, buf);

	if (ret < 0)
		return ret;
	if (ret < nbytes)
		return -EIO;

	for (i = nbytes - 1, *time = 0; i >= 0; i--)
		*time = (*time << 8) | buf[i];

	return 0;
}