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
struct rtc_time {int tm_mday; int tm_mon; int tm_year; int tm_sec; int tm_min; int tm_hour; } ;
struct nuc900_bcd_time {int bcd_mday; int bcd_mon; int bcd_year; int bcd_sec; int bcd_min; int bcd_hour; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static void nuc900_rtc_bin2bcd(struct device *dev, struct rtc_time *settm,
						struct nuc900_bcd_time *gettm)
{
	gettm->bcd_mday = bin2bcd(settm->tm_mday) << 0;
	gettm->bcd_mon  = bin2bcd(settm->tm_mon) << 8;

	if (settm->tm_year < 100) {
		dev_warn(dev, "The year will be between 1970-1999, right?\n");
		gettm->bcd_year = bin2bcd(settm->tm_year) << 16;
	} else {
		gettm->bcd_year = bin2bcd(settm->tm_year - 100) << 16;
	}

	gettm->bcd_sec  = bin2bcd(settm->tm_sec) << 0;
	gettm->bcd_min  = bin2bcd(settm->tm_min) << 8;
	gettm->bcd_hour = bin2bcd(settm->tm_hour) << 16;
}