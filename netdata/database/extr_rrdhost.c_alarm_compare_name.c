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
struct TYPE_2__ {scalar_t__ hash; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RRDCALC ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int alarm_compare_name(void *a, void *b) {
    RRDCALC *in1 = (RRDCALC *)a;
    RRDCALC *in2 = (RRDCALC *)b;

    if(in1->hash < in2->hash) return -1;
    else if(in1->hash > in2->hash) return 1;

    return strcmp(in1->name,in2->name);
}