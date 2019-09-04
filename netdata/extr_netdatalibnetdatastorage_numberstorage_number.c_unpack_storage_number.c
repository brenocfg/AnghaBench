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
typedef  int storage_number ;
typedef  int calculated_number ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

calculated_number unpack_storage_number(storage_number value) {
    if(!value) return 0;

    int sign = 0, exp = 0;
    int factor = 10;

    // bit 32 = 0:positive, 1:negative
    if(unlikely(value & (1 << 31)))
        sign = 1;

    // bit 31 = 0:divide, 1:multiply
    if(unlikely(value & (1 << 30)))
        exp = 1;

    // bit 27 SN_EXISTS_100
    if(unlikely(value & (1 << 26)))
        factor = 100;

    // bit 26 SN_EXISTS_RESET
    // bit 25 SN_EXISTS

    // bit 30, 29, 28 = (multiplier or divider) 0-7 (8 total)
    int mul = (value & ((1<<29)|(1<<28)|(1<<27))) >> 27;

    // bit 24 to bit 1 = the value, so remove all other bits
    value ^= value & ((1<<31)|(1<<30)|(1<<29)|(1<<28)|(1<<27)|(1<<26)|(1<<25)|(1<<24));

    calculated_number n = value;

    // fprintf(stderr, "UNPACK: %08X, sign = %d, exp = %d, mul = %d, factor = %d, n = " CALCULATED_NUMBER_FORMAT "\n", value, sign, exp, mul, factor, n);

    if(exp) {
        for(; mul; mul--)
            n *= factor;
    }
    else {
        for( ; mul ; mul--)
            n /= 10;
    }

    if(sign) n = -n;
    return n;
}