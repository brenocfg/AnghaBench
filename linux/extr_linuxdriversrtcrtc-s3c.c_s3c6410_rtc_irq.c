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
struct s3c_rtc {scalar_t__ base; int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int RTC_AF ; 
 int RTC_IRQF ; 
 scalar_t__ S3C2410_INTP ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void s3c6410_rtc_irq(struct s3c_rtc *info, int mask)
{
	rtc_update_irq(info->rtc, 1, RTC_AF | RTC_IRQF);
	writeb(mask, info->base + S3C2410_INTP);
}