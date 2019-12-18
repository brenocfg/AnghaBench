#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_int64 ;
struct TYPE_2__ {scalar_t__ a; } ;
typedef  TYPE_1__ diophantine_term_t ;

/* Variables and functions */

__attribute__((used)) static int
diophantine_sort_A(const void *xp, const void *yp)
{
    npy_int64 xa = ((diophantine_term_t*)xp)->a;
    npy_int64 ya = ((diophantine_term_t*)yp)->a;

    if (xa < ya) {
        return 1;
    }
    else if (ya < xa) {
        return -1;
    }
    else {
        return 0;
    }
}