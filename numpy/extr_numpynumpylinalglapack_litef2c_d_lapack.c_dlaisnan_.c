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
typedef  int logical ;
typedef  scalar_t__ doublereal ;

/* Variables and functions */

logical dlaisnan_(doublereal *din1, doublereal *din2)
{
    /* System generated locals */
    logical ret_val;


/*
    -- LAPACK auxiliary routine (version 3.2.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       June 2010


    Purpose
    =======

    This routine is not for general use.  It exists solely to avoid
    over-optimization in DISNAN.

    DLAISNAN checks for NaNs by comparing its two arguments for
    inequality.  NaN is the only floating-point value where NaN != NaN
    returns .TRUE.  To check for NaNs, pass the same variable as both
    arguments.

    A compiler must assume that the two arguments are
    not the same variable, and the test will not be optimized away.
    Interprocedural or whole-program optimization may delete this
    test.  The ISNAN functions will be replaced by the correct
    Fortran 03 intrinsic once the intrinsic is widely available.

    Arguments
    =========

    DIN1    (input) DOUBLE PRECISION

    DIN2    (input) DOUBLE PRECISION
            Two numbers to compare for inequality.

    =====================================================================
*/

    ret_val = *din1 != *din2;
    return ret_val;
}