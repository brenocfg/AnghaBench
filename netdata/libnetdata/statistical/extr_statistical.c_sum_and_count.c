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
typedef  scalar_t__ LONG_DOUBLE ;

/* Variables and functions */
 scalar_t__ NAN ; 
 scalar_t__ calculated_number_isnumber (scalar_t__ const) ; 
 scalar_t__ likely (size_t*) ; 
 scalar_t__ unlikely (int) ; 

inline LONG_DOUBLE sum_and_count(const LONG_DOUBLE *series, size_t entries, size_t *count) {
    const LONG_DOUBLE *value, *end = &series[entries];
    LONG_DOUBLE sum = 0;
    size_t c = 0;

    for(value = series; value < end ; value++) {
        if(calculated_number_isnumber(*value)) {
            sum += *value;
            c++;
        }
    }

    if(unlikely(!c)) sum = NAN;
    if(likely(count)) *count = c;

    return sum;
}