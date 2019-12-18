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
typedef  scalar_t__ npy_int16 ;
typedef  int npy_half ;

/* Variables and functions */
 int NPY_HALF_NAN ; 
 scalar_t__ npy_half_eq_nonan (int,int) ; 
 int /*<<< orphan*/  npy_half_isfinite (int) ; 
 scalar_t__ npy_half_isinf (int) ; 
 scalar_t__ npy_half_isnan (int) ; 
 scalar_t__ npy_half_iszero (int) ; 
 int /*<<< orphan*/  npy_set_floatstatus_invalid () ; 
 int /*<<< orphan*/  npy_set_floatstatus_overflow () ; 

npy_half npy_half_nextafter(npy_half x, npy_half y)
{
    npy_half ret;

    if (!npy_half_isfinite(x) || npy_half_isnan(y)) {
#if NPY_HALF_GENERATE_INVALID
        npy_set_floatstatus_invalid();
#endif
        ret = NPY_HALF_NAN;
    } else if (npy_half_eq_nonan(x, y)) {
        ret = x;
    } else if (npy_half_iszero(x)) {
        ret = (y&0x8000u) + 1; /* Smallest subnormal half */
    } else if (!(x&0x8000u)) { /* x > 0 */
        if ((npy_int16)x > (npy_int16)y) { /* x > y */
            ret = x-1;
        } else {
            ret = x+1;
        }
    } else {
        if (!(y&0x8000u) || (x&0x7fffu) > (y&0x7fffu)) { /* x < y */
            ret = x-1;
        } else {
            ret = x+1;
        }
    }
#if NPY_HALF_GENERATE_OVERFLOW
    if (npy_half_isinf(ret)) {
        npy_set_floatstatus_overflow();
    }
#endif

    return ret;
}