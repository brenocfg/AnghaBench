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
struct mutex {int dummy; } ;
struct m41t80_data {TYPE_1__* rtc; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct mutex ops_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int M41T80_ALMON_AFE ; 
 int M41T80_FLAGS_AF ; 
 int /*<<< orphan*/  M41T80_REG_ALARM_MON ; 
 int /*<<< orphan*/  M41T80_REG_FLAGS ; 
 unsigned long RTC_AF ; 
 struct m41t80_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_1__*,int,unsigned long) ; 

__attribute__((used)) static irqreturn_t m41t80_handle_irq(int irq, void *dev_id)
{
	struct i2c_client *client = dev_id;
	struct m41t80_data *m41t80 = i2c_get_clientdata(client);
	struct mutex *lock = &m41t80->rtc->ops_lock;
	unsigned long events = 0;
	int flags, flags_afe;

	mutex_lock(lock);

	flags_afe = i2c_smbus_read_byte_data(client, M41T80_REG_ALARM_MON);
	if (flags_afe < 0) {
		mutex_unlock(lock);
		return IRQ_NONE;
	}

	flags = i2c_smbus_read_byte_data(client, M41T80_REG_FLAGS);
	if (flags <= 0) {
		mutex_unlock(lock);
		return IRQ_NONE;
	}

	if (flags & M41T80_FLAGS_AF) {
		flags &= ~M41T80_FLAGS_AF;
		flags_afe &= ~M41T80_ALMON_AFE;
		events |= RTC_AF;
	}

	if (events) {
		rtc_update_irq(m41t80->rtc, 1, events);
		i2c_smbus_write_byte_data(client, M41T80_REG_FLAGS, flags);
		i2c_smbus_write_byte_data(client, M41T80_REG_ALARM_MON,
					  flags_afe);
	}

	mutex_unlock(lock);

	return IRQ_HANDLED;
}