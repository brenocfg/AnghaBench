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
struct TYPE_2__ {unsigned char tm_wday; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct i2c_client {scalar_t__ irq; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ABX8XX_IRQ_AIE ; 
 int /*<<< orphan*/  ABX8XX_REG_ASC ; 
 int /*<<< orphan*/  ABX8XX_REG_IRQ ; 
 unsigned char ABX8XX_STATUS_AF ; 
 int EINVAL ; 
 void* bcd2bin (unsigned char) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int abx80x_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char buf[7];

	int irq_mask, err;

	if (client->irq <= 0)
		return -EINVAL;

	err = i2c_smbus_read_i2c_block_data(client, ABX8XX_REG_ASC,
					    sizeof(buf), buf);
	if (err)
		return err;

	irq_mask = i2c_smbus_read_byte_data(client, ABX8XX_REG_IRQ);
	if (irq_mask < 0)
		return irq_mask;

	t->time.tm_sec = bcd2bin(buf[0] & 0x7F);
	t->time.tm_min = bcd2bin(buf[1] & 0x7F);
	t->time.tm_hour = bcd2bin(buf[2] & 0x3F);
	t->time.tm_mday = bcd2bin(buf[3] & 0x3F);
	t->time.tm_mon = bcd2bin(buf[4] & 0x1F) - 1;
	t->time.tm_wday = buf[5] & 0x7;

	t->enabled = !!(irq_mask & ABX8XX_IRQ_AIE);
	t->pending = (buf[6] & ABX8XX_STATUS_AF) && t->enabled;

	return err;
}