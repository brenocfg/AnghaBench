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
typedef  int npy_uint64 ;
typedef  size_t NPY_DATETIMEUNIT ;

/* Variables and functions */
 int* _datetime_factors ; 

__attribute__((used)) static npy_uint64
get_datetime_units_factor(NPY_DATETIMEUNIT bigbase, NPY_DATETIMEUNIT littlebase)
{
    npy_uint64 factor = 1;
    NPY_DATETIMEUNIT unit = bigbase;

    while (unit < littlebase) {
        factor *= _datetime_factors[unit];
        /*
         * Detect overflow by disallowing the top 16 bits to be 1.
         * That allows a margin of error much bigger than any of
         * the datetime factors.
         */
        if (factor&0xff00000000000000ULL) {
            return 0;
        }
        ++unit;
    }
    return factor;
}