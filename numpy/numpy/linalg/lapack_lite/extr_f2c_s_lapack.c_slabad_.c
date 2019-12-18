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

/* Variables and functions */
 float r_lg10 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqrt (int /*<<< orphan*/ ) ; 

int slabad_(real *small, real *large)
{

/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    SLABAD takes as input the values computed by SLAMCH for underflow and
    overflow, and returns the square root of each of these values if the
    log of LARGE is sufficiently large.  This subroutine is intended to
    identify machines with a large exponent range, such as the Crays, and
    redefine the underflow and overflow limits to be the square roots of
    the values computed by SLAMCH.  This subroutine is needed because
    SLAMCH does not compensate for poor arithmetic in the upper half of
    the exponent range, as is found on a Cray.

    Arguments
    =========

    SMALL   (input/output) REAL
            On entry, the underflow threshold as computed by SLAMCH.
            On exit, if LOG10(LARGE) is sufficiently large, the square
            root of SMALL, otherwise unchanged.

    LARGE   (input/output) REAL
            On entry, the overflow threshold as computed by SLAMCH.
            On exit, if LOG10(LARGE) is sufficiently large, the square
            root of LARGE, otherwise unchanged.

    =====================================================================


       If it looks like we're on a Cray, take the square root of
       SMALL and LARGE to avoid overflow and underflow problems.
*/

    if (r_lg10(large) > 2e3f) {
	*small = sqrt(*small);
	*large = sqrt(*large);
    }

    return 0;

/*     End of SLABAD */

}