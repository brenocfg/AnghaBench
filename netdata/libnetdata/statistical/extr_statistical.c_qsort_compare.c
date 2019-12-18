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
 scalar_t__ isinf (scalar_t__) ; 
 scalar_t__ isnan (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qsort_compare(const void *a, const void *b) {
    LONG_DOUBLE *p1 = (LONG_DOUBLE *)a, *p2 = (LONG_DOUBLE *)b;
    LONG_DOUBLE n1 = *p1, n2 = *p2;

    if(unlikely(isnan(n1) || isnan(n2))) {
        if(isnan(n1) && !isnan(n2)) return -1;
        if(!isnan(n1) && isnan(n2)) return 1;
        return 0;
    }
    if(unlikely(isinf(n1) || isinf(n2))) {
        if(!isinf(n1) && isinf(n2)) return -1;
        if(isinf(n1) && !isinf(n2)) return 1;
        return 0;
    }

    if(unlikely(n1 < n2)) return -1;
    if(unlikely(n1 > n2)) return 1;
    return 0;
}