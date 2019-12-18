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
struct TYPE_3__ {int top; int dmax; scalar_t__* d; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */

void bn_set_all_zero(BIGNUM *a)
{
    int i;

    for (i = a->top; i < a->dmax; i++)
        a->d[i] = 0;
}