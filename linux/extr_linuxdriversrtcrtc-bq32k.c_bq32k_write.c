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
typedef  scalar_t__ uint8_t ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAX_LEN ; 
 scalar_t__ i2c_master_send (struct i2c_client*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int bq32k_write(struct device *dev, void *data, uint8_t off, uint8_t len)
{
	struct i2c_client *client = to_i2c_client(dev);
	uint8_t buffer[MAX_LEN + 1];

	buffer[0] = off;
	memcpy(&buffer[1], data, len);

	if (i2c_master_send(client, buffer, len + 1) == len + 1)
		return 0;

	return -EIO;
}