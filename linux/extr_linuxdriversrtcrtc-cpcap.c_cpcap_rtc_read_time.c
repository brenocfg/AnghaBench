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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct cpcap_time {int day; int tod1; int tod2; } ;
struct cpcap_rtc {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_REG_DAY ; 
 int /*<<< orphan*/  CPCAP_REG_TOD1 ; 
 int /*<<< orphan*/  CPCAP_REG_TOD2 ; 
 int EIO ; 
 int /*<<< orphan*/  cpcap2rtc_time (struct rtc_time*,struct cpcap_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct cpcap_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int cpcap_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct cpcap_rtc *rtc;
	struct cpcap_time cpcap_tm;
	int temp_tod2;
	int ret;

	rtc = dev_get_drvdata(dev);

	ret = regmap_read(rtc->regmap, CPCAP_REG_TOD2, &temp_tod2);
	ret |= regmap_read(rtc->regmap, CPCAP_REG_DAY, &cpcap_tm.day);
	ret |= regmap_read(rtc->regmap, CPCAP_REG_TOD1, &cpcap_tm.tod1);
	ret |= regmap_read(rtc->regmap, CPCAP_REG_TOD2, &cpcap_tm.tod2);

	if (temp_tod2 > cpcap_tm.tod2)
		ret |= regmap_read(rtc->regmap, CPCAP_REG_DAY, &cpcap_tm.day);

	if (ret) {
		dev_err(dev, "Failed to read time\n");
		return -EIO;
	}

	cpcap2rtc_time(tm, &cpcap_tm);

	return 0;
}