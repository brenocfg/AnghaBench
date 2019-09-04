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
typedef  int /*<<< orphan*/  real ;
typedef  int /*<<< orphan*/  logical ;

/* Variables and functions */

logical sisnan_(real *sin__)
{
    /* System generated locals */
    logical ret_val;

    /* Local variables */
    extern logical slaisnan_(real *, real *);


/*
    -- LAPACK auxiliary routine (version 3.2.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       June 2010


    Purpose
    =======

    SISNAN returns .TRUE. if its argument is NaN, and .FALSE.
    otherwise.  To be replaced by the Fortran 2003 intrinsic in the
    future.

    Arguments
    =========

    SIN     (input) REAL
            Input to test for NaN.

    =====================================================================
*/

    ret_val = slaisnan_(sin__, sin__);
    return ret_val;
}