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
struct rs5c372 {unsigned char* regs; int /*<<< orphan*/  has_irq; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int RS5C_ADDR (size_t) ; 
 unsigned char RS5C_CTRL1_AALE ; 
 size_t RS5C_REG_CTRL1 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct rs5c372* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int,unsigned char) ; 
 int rs5c_get_regs (struct rs5c372*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int rs5c_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct i2c_client	*client = to_i2c_client(dev);
	struct rs5c372		*rs5c = i2c_get_clientdata(client);
	unsigned char		buf;
	int			status, addr;

	buf = rs5c->regs[RS5C_REG_CTRL1];

	if (!rs5c->has_irq)
		return -EINVAL;

	status = rs5c_get_regs(rs5c);
	if (status < 0)
		return status;

	addr = RS5C_ADDR(RS5C_REG_CTRL1);
	if (enabled)
		buf |= RS5C_CTRL1_AALE;
	else
		buf &= ~RS5C_CTRL1_AALE;

	if (i2c_smbus_write_byte_data(client, addr, buf) < 0) {
		dev_warn(dev, "can't update alarm\n");
		status = -EIO;
	} else
		rs5c->regs[RS5C_REG_CTRL1] = buf;

	return status;
}