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
 int /*<<< orphan*/  BRK_IF_RTC_CTRS_ALIGN (unsigned long long,unsigned long long) ; 
 unsigned long long PRCMSlowClkCtrFastGet () ; 

__attribute__((used)) static unsigned long long RTCFastDomainCounterGet (void) {

    #define BRK_IF_RTC_CTRS_ALIGN(c2, c1)       if (c2 - c1 <= 1) {     \
                                                    itr++;              \
                                                    break;              \
                                                }

    unsigned long long rtc_count1, rtc_count2, rtc_count3;
    unsigned int itr;

    do {
        rtc_count1 = PRCMSlowClkCtrFastGet();
        rtc_count2 = PRCMSlowClkCtrFastGet();
        rtc_count3 = PRCMSlowClkCtrFastGet();
        itr = 0;

        BRK_IF_RTC_CTRS_ALIGN(rtc_count2, rtc_count1);
        BRK_IF_RTC_CTRS_ALIGN(rtc_count3, rtc_count2);
        BRK_IF_RTC_CTRS_ALIGN(rtc_count3, rtc_count1);

        // Consistent values in two consecutive reads implies a correct
        // value of the counter. Do note, the counter does not give the
        // calendar time but a hardware that ticks upwards continuously.
        // The 48-bit counter operates at 32,768 HZ.

    } while (true);

    return (1 == itr) ? rtc_count2 : rtc_count3;
}