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
typedef  int /*<<< orphan*/  logical ;
typedef  int /*<<< orphan*/  doublereal ;

/* Variables and functions */

logical disnan_(doublereal *din)
{
    /* System generated locals */
    logical ret_val;

    /* Local variables */
    extern logical dlaisnan_(doublereal *, doublereal *);


/*
    -- LAPACK auxiliary routine (version 3.2.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       June 2010


    Purpose
    =======

    DISNAN returns .TRUE. if its argument is NaN, and .FALSE.
    otherwise.  To be replaced by the Fortran 2003 intrinsic in the
    future.

    Arguments
    =========

    DIN     (input) DOUBLE PRECISION
            Input to test for NaN.

    =====================================================================
*/

    ret_val = dlaisnan_(din, din);
    return ret_val;
}