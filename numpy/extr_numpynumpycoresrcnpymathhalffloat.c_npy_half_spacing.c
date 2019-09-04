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
typedef  int npy_uint16 ;
typedef  int npy_half ;

/* Variables and functions */
 int NPY_HALF_NAN ; 
 int NPY_HALF_PINF ; 

npy_half npy_half_spacing(npy_half h)
{
    npy_half ret;
    npy_uint16 h_exp = h&0x7c00u;
    npy_uint16 h_sig = h&0x03ffu;
    if (h_exp == 0x7c00u) {
#if NPY_HALF_GENERATE_INVALID
        npy_set_floatstatus_invalid();
#endif
        ret = NPY_HALF_NAN;
    } else if (h == 0x7bffu) {
#if NPY_HALF_GENERATE_OVERFLOW
        npy_set_floatstatus_overflow();
#endif
        ret = NPY_HALF_PINF;
    } else if ((h&0x8000u) && h_sig == 0) { /* Negative boundary case */
        if (h_exp > 0x2c00u) { /* If result is normalized */
            ret = h_exp - 0x2c00u;
        } else if(h_exp > 0x0400u) { /* The result is a subnormal, but not the smallest */
            ret = 1 << ((h_exp >> 10) - 2);
        } else {
            ret = 0x0001u; /* Smallest subnormal half */
        }
    } else if (h_exp > 0x2800u) { /* If result is still normalized */
        ret = h_exp - 0x2800u;
    } else if (h_exp > 0x0400u) { /* The result is a subnormal, but not the smallest */
        ret = 1 << ((h_exp >> 10) - 1);
    } else {
        ret = 0x0001u;
    }

    return ret;
}