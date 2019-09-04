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
typedef  int /*<<< orphan*/  LONG_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_compare ; 

inline void sort_series(LONG_DOUBLE *series, size_t entries) {
    qsort(series, entries, sizeof(LONG_DOUBLE), qsort_compare);
}