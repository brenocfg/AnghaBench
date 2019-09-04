#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int f; } ;
typedef  TYPE_1__ calc_number_t ;

/* Variables and functions */
 int CALC_PI ; 

void rpn_2pi(calc_number_t *c)
{
    c->f = CALC_PI*2;
}