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
typedef  int npy_uint32 ;
typedef  int npy_uint16 ;

/* Variables and functions */

npy_uint32 npy_halfbits_to_floatbits(npy_uint16 h)
{
    npy_uint16 h_exp, h_sig;
    npy_uint32 f_sgn, f_exp, f_sig;

    h_exp = (h&0x7c00u);
    f_sgn = ((npy_uint32)h&0x8000u) << 16;
    switch (h_exp) {
        case 0x0000u: /* 0 or subnormal */
            h_sig = (h&0x03ffu);
            /* Signed zero */
            if (h_sig == 0) {
                return f_sgn;
            }
            /* Subnormal */
            h_sig <<= 1;
            while ((h_sig&0x0400u) == 0) {
                h_sig <<= 1;
                h_exp++;
            }
            f_exp = ((npy_uint32)(127 - 15 - h_exp)) << 23;
            f_sig = ((npy_uint32)(h_sig&0x03ffu)) << 13;
            return f_sgn + f_exp + f_sig;
        case 0x7c00u: /* inf or NaN */
            /* All-ones exponent and a copy of the significand */
            return f_sgn + 0x7f800000u + (((npy_uint32)(h&0x03ffu)) << 13);
        default: /* normalized */
            /* Just need to adjust the exponent and shift */
            return f_sgn + (((npy_uint32)(h&0x7fffu) + 0x1c000u) << 13);
    }
}