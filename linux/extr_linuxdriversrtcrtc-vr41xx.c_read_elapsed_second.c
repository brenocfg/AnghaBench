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
typedef  int u64 ;
typedef  int time64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEHREG ; 
 int /*<<< orphan*/  ETIMELREG ; 
 int /*<<< orphan*/  ETIMEMREG ; 
 unsigned long rtc1_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline time64_t read_elapsed_second(void)
{

	unsigned long first_low, first_mid, first_high;

	unsigned long second_low, second_mid, second_high;

	do {
		first_low = rtc1_read(ETIMELREG);
		first_mid = rtc1_read(ETIMEMREG);
		first_high = rtc1_read(ETIMEHREG);
		second_low = rtc1_read(ETIMELREG);
		second_mid = rtc1_read(ETIMEMREG);
		second_high = rtc1_read(ETIMEHREG);
	} while (first_low != second_low || first_mid != second_mid ||
		 first_high != second_high);

	return ((u64)first_high << 17) | (first_mid << 1) | (first_low >> 15);
}