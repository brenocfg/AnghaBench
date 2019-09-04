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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ IL39_RTC_DATA_LOWER_BOUND ; 
 scalar_t__ IL39_RTC_DATA_UPPER_BOUND ; 

__attribute__((used)) static inline int
il3945_hw_valid_rtc_data_addr(u32 addr)
{
	return (addr >= IL39_RTC_DATA_LOWER_BOUND &&
		addr < IL39_RTC_DATA_UPPER_BOUND);
}