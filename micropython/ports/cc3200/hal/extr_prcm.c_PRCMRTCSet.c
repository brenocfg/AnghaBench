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
 int /*<<< orphan*/  RTC_MSEC_IN_U64MSEC (unsigned long long) ; 
 int /*<<< orphan*/  RTC_SECS_IN_U64MSEC (unsigned long long) ; 
 int /*<<< orphan*/  RTC_U32MSEC_REG_WR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_U32SECS_REG_WR (int /*<<< orphan*/ ) ; 
 unsigned long long RTC_U64MSEC_MK (unsigned long,unsigned short) ; 
 unsigned long long SCC_U64MSEC_GET () ; 

void PRCMRTCSet(unsigned long ulSecs, unsigned short usMsec)
{
        unsigned long long ullMsec = 0;

        if(IS_RTC_USED()) {
                ullMsec = RTC_U64MSEC_MK(ulSecs, usMsec) - SCC_U64MSEC_GET();

                 RTC_U32SECS_REG_WR(RTC_SECS_IN_U64MSEC(ullMsec));
                 RTC_U32MSEC_REG_WR(RTC_MSEC_IN_U64MSEC(ullMsec));
        }

        return;
}