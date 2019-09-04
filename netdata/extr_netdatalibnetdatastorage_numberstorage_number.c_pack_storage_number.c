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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int storage_number ;
typedef  double calculated_number ;

/* Variables and functions */
 int SN_EXISTS_100 ; 
 int get_storage_number_flags (int /*<<< orphan*/ ) ; 

storage_number pack_storage_number(calculated_number value, uint32_t flags) {
    // bit 32 = sign 0:positive, 1:negative
    // bit 31 = 0:divide, 1:multiply
    // bit 30, 29, 28 = (multiplier or divider) 0-7 (8 total)
    // bit 27 SN_EXISTS_100
    // bit 26 SN_EXISTS_RESET
    // bit 25 SN_EXISTS
    // bit 24 to bit 1 = the value

    storage_number r = get_storage_number_flags(flags);
    if(!value) return r;

    int m = 0;
    calculated_number n = value, factor = 10;

    // if the value is negative
    // add the sign bit and make it positive
    if(n < 0) {
        r += (1 << 31); // the sign bit 32
        n = -n;
    }

    if(n / 10000000.0 > 0x00ffffff) {
        factor = 100;
        r |= SN_EXISTS_100;
    }

    // make its integer part fit in 0x00ffffff
    // by dividing it by 10 up to 7 times
    // and increasing the multiplier
    while(m < 7 && n > (calculated_number)0x00ffffff) {
        n /= factor;
        m++;
    }

    if(m) {
        // the value was too big and we divided it
        // so we add a multiplier to unpack it
        r += (1 << 30) + (m << 27); // the multiplier m

        if(n > (calculated_number)0x00ffffff) {
            #ifdef NETDATA_INTERNAL_CHECKS
            error("Number " CALCULATED_NUMBER_FORMAT " is too big.", value);
            #endif
            r += 0x00ffffff;
            return r;
        }
    }
    else {
        // 0x0019999e is the number that can be multiplied
        // by 10 to give 0x00ffffff
        // while the value is below 0x0019999e we can
        // multiply it by 10, up to 7 times, increasing
        // the multiplier
        while(m < 7 && n < (calculated_number)0x0019999e) {
            n *= 10;
            m++;
        }

        // the value was small enough and we multiplied it
        // so we add a divider to unpack it
        r += (0 << 30) + (m << 27); // the divider m
    }

#ifdef STORAGE_WITH_MATH
    // without this there are rounding problems
    // example: 0.9 becomes 0.89
    r += lrint((double) n);
#else
    r += (storage_number)n;
#endif

    return r;
}