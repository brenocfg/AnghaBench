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
typedef  int /*<<< orphan*/  u8 ;
struct tps80031_rtc {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALARM_INT_STATUS ; 
 int /*<<< orphan*/  TPS80031_RTC_STATUS_REG ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int tps80031_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tps80031_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clear_alarm_int_status(struct device *dev, struct tps80031_rtc *rtc)
{
	int ret;
	u8 buf;

	/**
	 * As per datasheet, A dummy read of this  RTC_STATUS_REG register
	 * is necessary before each I2C read in order to update the status
	 * register value.
	 */
	ret = tps80031_read(dev->parent, TPS80031_SLAVE_ID1,
				TPS80031_RTC_STATUS_REG, &buf);
	if (ret < 0) {
		dev_err(dev, "reading RTC_STATUS failed. err = %d\n", ret);
		return ret;
	}

	/* clear Alarm status bits.*/
	ret = tps80031_set_bits(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_RTC_STATUS_REG, ALARM_INT_STATUS);
	if (ret < 0) {
		dev_err(dev, "clear Alarm INT failed, err = %d\n", ret);
		return ret;
	}
	return 0;
}