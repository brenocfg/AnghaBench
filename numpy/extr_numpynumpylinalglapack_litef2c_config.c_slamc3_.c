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
typedef  scalar_t__ real ;
typedef  scalar_t__ doublereal ;

/* Variables and functions */

doublereal slamc3_(real *a, real *b)
{
    /* System generated locals */
    real ret_val;


/*
    -- LAPACK auxiliary routine (version 3.2) --
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..
       November 2006


    Purpose
    =======

    SLAMC3  is intended to force  A  and  B  to be stored prior to doing
    the addition of  A  and  B ,  for use in situations where optimizers
    might hold one of these in a register.

    Arguments
    =========

    A       (input) REAL
    B       (input) REAL
            The values A and B.

   =====================================================================
*/


    ret_val = *a + *b;

    return ret_val;

/*     End of SLAMC3 */

}