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
 unsigned short RTC_U32MSEC_REG_RD () ; 
 unsigned long RTC_U32SECS_REG_RD () ; 
 unsigned long long RTC_U64MSEC_MK (unsigned long,unsigned short) ; 
 int /*<<< orphan*/  SCC_U64MSEC_MATCH_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECT_SCC_U42BITS (unsigned long long) ; 

void PRCMRTCMatchSet(unsigned long ulSecs, unsigned short usMsec)
{
        unsigned long long ullMsec = 0;

        if(IS_RTC_USED()) {
                ullMsec  = RTC_U64MSEC_MK(ulSecs, usMsec);
                ullMsec -= RTC_U64MSEC_MK(RTC_U32SECS_REG_RD(),
                                          RTC_U32MSEC_REG_RD());
                SCC_U64MSEC_MATCH_SET(SELECT_SCC_U42BITS(ullMsec));
        }

        return;
}