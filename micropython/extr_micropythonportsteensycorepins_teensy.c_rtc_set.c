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

/* Variables and functions */
 scalar_t__ RTC_SR ; 
 scalar_t__ RTC_SR_TCE ; 
 scalar_t__ RTC_TPR ; 
 unsigned long RTC_TSR ; 

void rtc_set(unsigned long t)
{
	RTC_SR = 0;
	RTC_TPR = 0;
	RTC_TSR = t;
	RTC_SR = RTC_SR_TCE;
}