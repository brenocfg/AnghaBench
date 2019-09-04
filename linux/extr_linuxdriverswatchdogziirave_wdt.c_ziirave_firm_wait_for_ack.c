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
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int ZIIRAVE_FIRM_DOWNLOAD_ACK ; 
 int ZIIRAVE_FIRM_DOWNLOAD_BUSY ; 
 int /*<<< orphan*/  ZIIRAVE_FIRM_WAIT_FOR_ACK_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ziirave_firm_wait_for_ack(struct watchdog_device *wdd)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	int ret;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(ZIIRAVE_FIRM_WAIT_FOR_ACK_TIMEOUT);
	do {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;

		usleep_range(5000, 10000);

		ret = i2c_smbus_read_byte(client);
		if (ret < 0) {
			dev_err(&client->dev, "Failed to read byte\n");
			return ret;
		}
	} while (ret == ZIIRAVE_FIRM_DOWNLOAD_BUSY);

	return ret == ZIIRAVE_FIRM_DOWNLOAD_ACK ? 0 : -EIO;
}