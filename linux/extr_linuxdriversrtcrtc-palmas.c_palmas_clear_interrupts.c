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
struct palmas {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_RTC_BASE ; 
 int /*<<< orphan*/  PALMAS_RTC_STATUS_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct palmas* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int palmas_read (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int palmas_write (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int palmas_clear_interrupts(struct device *dev)
{
	struct palmas *palmas = dev_get_drvdata(dev->parent);
	unsigned int rtc_reg;
	int ret;

	ret = palmas_read(palmas, PALMAS_RTC_BASE, PALMAS_RTC_STATUS_REG,
				&rtc_reg);
	if (ret < 0) {
		dev_err(dev, "RTC_STATUS read failed, err = %d\n", ret);
		return ret;
	}

	ret = palmas_write(palmas, PALMAS_RTC_BASE, PALMAS_RTC_STATUS_REG,
			rtc_reg);
	if (ret < 0) {
		dev_err(dev, "RTC_STATUS write failed, err = %d\n", ret);
		return ret;
	}
	return 0;
}