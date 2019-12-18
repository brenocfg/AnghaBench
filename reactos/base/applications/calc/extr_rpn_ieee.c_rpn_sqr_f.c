#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int f; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_7__ {void* is_nan; } ;

/* Variables and functions */
 void* TRUE ; 
 scalar_t__ _finite (int) ; 
 scalar_t__ _isnan (int) ; 
 TYPE_5__ calc ; 
 int pow (int,int) ; 

__attribute__((used)) static void rpn_sqr_f(calc_number_t *r, calc_number_t *a, calc_number_t *b)
{
    if (b->f == 0)
        calc.is_nan = TRUE;
    else {
        r->f = pow(a->f, 1./b->f);
        if (_finite(r->f) == 0 || _isnan(r->f))
            calc.is_nan = TRUE;
    }
}