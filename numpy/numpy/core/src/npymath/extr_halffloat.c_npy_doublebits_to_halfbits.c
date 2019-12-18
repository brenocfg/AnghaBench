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
typedef  int npy_uint64 ;
typedef  int npy_uint16 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  npy_set_floatstatus_overflow () ; 
 int /*<<< orphan*/  npy_set_floatstatus_underflow () ; 

npy_uint16 npy_doublebits_to_halfbits(npy_uint64 d)
{
    npy_uint64 d_exp, d_sig;
    npy_uint16 h_sgn, h_exp, h_sig;

    h_sgn = (d&0x8000000000000000ULL) >> 48;
    d_exp = (d&0x7ff0000000000000ULL);

    /* Exponent overflow/NaN converts to signed inf/NaN */
    if (d_exp >= 0x40f0000000000000ULL) {
        if (d_exp == 0x7ff0000000000000ULL) {
            /* Inf or NaN */
            d_sig = (d&0x000fffffffffffffULL);
            if (d_sig != 0) {
                /* NaN - propagate the flag in the significand... */
                npy_uint16 ret = (npy_uint16) (0x7c00u + (d_sig >> 42));
                /* ...but make sure it stays a NaN */
                if (ret == 0x7c00u) {
                    ret++;
                }
                return h_sgn + ret;
            } else {
                /* signed inf */
                return h_sgn + 0x7c00u;
            }
        } else {
            /* overflow to signed inf */
#if NPY_HALF_GENERATE_OVERFLOW
            npy_set_floatstatus_overflow();
#endif
            return h_sgn + 0x7c00u;
        }
    }

    /* Exponent underflow converts to subnormal half or signed zero */
    if (d_exp <= 0x3f00000000000000ULL) {
        /*
         * Signed zeros, subnormal floats, and floats with small
         * exponents all convert to signed zero half-floats.
         */
        if (d_exp < 0x3e60000000000000ULL) {
#if NPY_HALF_GENERATE_UNDERFLOW
            /* If d != 0, it underflowed to 0 */
            if ((d&0x7fffffffffffffffULL) != 0) {
                npy_set_floatstatus_underflow();
            }
#endif
            return h_sgn;
        }
        /* Make the subnormal significand */
        d_exp >>= 52;
        d_sig = (0x0010000000000000ULL + (d&0x000fffffffffffffULL));
#if NPY_HALF_GENERATE_UNDERFLOW
        /* If it's not exactly represented, it underflowed */
        if ((d_sig&(((npy_uint64)1 << (1051 - d_exp)) - 1)) != 0) {
            npy_set_floatstatus_underflow();
        }
#endif
        /*
         * Unlike floats, doubles have enough room to shift left to align
         * the subnormal significand leading to no loss of the last bits.
         * The smallest possible exponent giving a subnormal is:
         * `d_exp = 0x3e60000000000000 >> 52 = 998`. All larger subnormals are
         * shifted with respect to it. This adds a shift of 10+1 bits the final
         * right shift when comparing it to the one in the normal branch.
         */
        assert(d_exp - 998 >= 0);
        d_sig <<= (d_exp - 998);
        /* Handle rounding by adding 1 to the bit beyond half precision */
#if NPY_HALF_ROUND_TIES_TO_EVEN
        /*
         * If the last bit in the half significand is 0 (already even), and
         * the remaining bit pattern is 1000...0, then we do not add one
         * to the bit after the half significand.  In all other cases, we do.
         */
        if ((d_sig&0x003fffffffffffffULL) != 0x0010000000000000ULL) {
            d_sig += 0x0010000000000000ULL;
        }
#else
        d_sig += 0x0010000000000000ULL;
#endif
        h_sig = (npy_uint16) (d_sig >> 53);
        /*
         * If the rounding causes a bit to spill into h_exp, it will
         * increment h_exp from zero to one and h_sig will be zero.
         * This is the correct result.
         */
        return h_sgn + h_sig;
    }

    /* Regular case with no overflow or underflow */
    h_exp = (npy_uint16) ((d_exp - 0x3f00000000000000ULL) >> 42);
    /* Handle rounding by adding 1 to the bit beyond half precision */
    d_sig = (d&0x000fffffffffffffULL);
#if NPY_HALF_ROUND_TIES_TO_EVEN
    /*
     * If the last bit in the half significand is 0 (already even), and
     * the remaining bit pattern is 1000...0, then we do not add one
     * to the bit after the half significand.  In all other cases, we do.
     */
    if ((d_sig&0x000007ffffffffffULL) != 0x0000020000000000ULL) {
        d_sig += 0x0000020000000000ULL;
    }
#else
    d_sig += 0x0000020000000000ULL;
#endif
    h_sig = (npy_uint16) (d_sig >> 42);

    /*
     * If the rounding causes a bit to spill into h_exp, it will
     * increment h_exp by one and h_sig will be zero.  This is the
     * correct result.  h_exp may increment to 15, at greatest, in
     * which case the result overflows to a signed inf.
     */
#if NPY_HALF_GENERATE_OVERFLOW
    h_sig += h_exp;
    if (h_sig == 0x7c00u) {
        npy_set_floatstatus_overflow();
    }
    return h_sgn + h_sig;
#else
    return h_sgn + h_exp + h_sig;
#endif
}