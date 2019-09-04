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
struct TYPE_2__ {int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct rs5c372 {int* regs; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RS5C_CTRL1_AALE ; 
 int RS5C_CTRL2_AAFG ; 
 size_t RS5C_REG_ALARM_A_HOURS ; 
 size_t RS5C_REG_ALARM_A_MIN ; 
 size_t RS5C_REG_CTRL1 ; 
 size_t RS5C_REG_CTRL2 ; 
 int /*<<< orphan*/  bcd2bin (int) ; 
 struct rs5c372* i2c_get_clientdata (struct i2c_client*) ; 
 int rs5c_get_regs (struct rs5c372*) ; 
 int /*<<< orphan*/  rs5c_reg2hr (struct rs5c372*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int rs5c_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client	*client = to_i2c_client(dev);
	struct rs5c372		*rs5c = i2c_get_clientdata(client);
	int			status;

	status = rs5c_get_regs(rs5c);
	if (status < 0)
		return status;

	/* report alarm time */
	t->time.tm_sec = 0;
	t->time.tm_min = bcd2bin(rs5c->regs[RS5C_REG_ALARM_A_MIN] & 0x7f);
	t->time.tm_hour = rs5c_reg2hr(rs5c, rs5c->regs[RS5C_REG_ALARM_A_HOURS]);

	/* ... and status */
	t->enabled = !!(rs5c->regs[RS5C_REG_CTRL1] & RS5C_CTRL1_AALE);
	t->pending = !!(rs5c->regs[RS5C_REG_CTRL2] & RS5C_CTRL2_AAFG);

	return 0;
}