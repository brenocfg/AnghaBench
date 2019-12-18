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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ id; } ;
typedef  TYPE_1__ RRDCALC ;

/* Variables and functions */

int alarm_compare_id(void *a, void *b) {
    register uint32_t hash1 = ((RRDCALC *)a)->id;
    register uint32_t hash2 = ((RRDCALC *)b)->id;

    if(hash1 < hash2) return -1;
    else if(hash1 > hash2) return 1;

    return 0;
}