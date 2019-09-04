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
struct TYPE_2__ {void* tm_sec; void* tm_min; void* tm_hour; void* tm_yday; void* tm_wday; void* tm_mday; void* tm_mon; void* tm_year; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct device {int dummy; } ;
struct asm9260_rtc_priv {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ HW_ALDOM ; 
 scalar_t__ HW_ALDOW ; 
 scalar_t__ HW_ALDOY ; 
 scalar_t__ HW_ALHOUR ; 
 scalar_t__ HW_ALMIN ; 
 scalar_t__ HW_ALMON ; 
 scalar_t__ HW_ALSEC ; 
 scalar_t__ HW_ALYEAR ; 
 scalar_t__ HW_AMR ; 
 scalar_t__ HW_CIIR ; 
 struct asm9260_rtc_priv* dev_get_drvdata (struct device*) ; 
 void* ioread32 (scalar_t__) ; 
 int rtc_valid_tm (TYPE_1__*) ; 

__attribute__((used)) static int asm9260_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct asm9260_rtc_priv *priv = dev_get_drvdata(dev);

	alrm->time.tm_year = ioread32(priv->iobase + HW_ALYEAR);
	alrm->time.tm_mon  = ioread32(priv->iobase + HW_ALMON);
	alrm->time.tm_mday = ioread32(priv->iobase + HW_ALDOM);
	alrm->time.tm_wday = ioread32(priv->iobase + HW_ALDOW);
	alrm->time.tm_yday = ioread32(priv->iobase + HW_ALDOY);
	alrm->time.tm_hour = ioread32(priv->iobase + HW_ALHOUR);
	alrm->time.tm_min  = ioread32(priv->iobase + HW_ALMIN);
	alrm->time.tm_sec  = ioread32(priv->iobase + HW_ALSEC);

	alrm->enabled = ioread32(priv->iobase + HW_AMR) ? 1 : 0;
	alrm->pending = ioread32(priv->iobase + HW_CIIR) ? 1 : 0;

	return rtc_valid_tm(&alrm->time);
}