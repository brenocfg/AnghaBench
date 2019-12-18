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
typedef  int const LONG_DOUBLE ;

/* Variables and functions */
 int const NAN ; 
 int* copy_series (int const*,size_t) ; 
 int /*<<< orphan*/  freez (int const*) ; 
 int median_on_sorted_series (int const*,size_t) ; 
 int /*<<< orphan*/  sort_series (int const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

LONG_DOUBLE median(const LONG_DOUBLE *series, size_t entries) {
    if(unlikely(entries == 0)) return NAN;
    if(unlikely(entries == 1)) return series[0];

    if(unlikely(entries == 2))
        return (series[0] + series[1]) / 2;

    LONG_DOUBLE *copy = copy_series(series, entries);
    sort_series(copy, entries);

    LONG_DOUBLE avg = median_on_sorted_series(copy, entries);

    freez(copy);
    return avg;
}