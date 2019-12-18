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
 scalar_t__ IS_RTC_USED () ; 
 unsigned short RTC_MSEC_IN_U64MSEC (unsigned long long) ; 
 unsigned long RTC_SECS_IN_U64MSEC (unsigned long long) ; 
 int /*<<< orphan*/  RTC_U32MSEC_REG_RD () ; 
 int /*<<< orphan*/  RTC_U32SECS_REG_RD () ; 
 scalar_t__ RTC_U64MSEC_MK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long SCC_U64MSEC_MATCH_GET () ; 

void PRCMRTCMatchGet(unsigned long *ulSecs, unsigned short *usMsec)
{
        unsigned long long ullMsec = 0;

        if(IS_RTC_USED()) {
                ullMsec  = SCC_U64MSEC_MATCH_GET();
                ullMsec += RTC_U64MSEC_MK(RTC_U32SECS_REG_RD(),
                                          RTC_U32MSEC_REG_RD());
        }

        *ulSecs = RTC_SECS_IN_U64MSEC(ullMsec);
        *usMsec = RTC_MSEC_IN_U64MSEC(ullMsec);

        return;
}