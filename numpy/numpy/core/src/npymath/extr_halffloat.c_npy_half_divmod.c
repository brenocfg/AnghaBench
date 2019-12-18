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
typedef  int /*<<< orphan*/  npy_half ;

/* Variables and functions */
 float npy_divmodf (float,float,float*) ; 
 int /*<<< orphan*/  npy_float_to_half (float) ; 
 float npy_half_to_float (int /*<<< orphan*/ ) ; 

npy_half npy_half_divmod(npy_half h1, npy_half h2, npy_half *modulus)
{
    float fh1 = npy_half_to_float(h1);
    float fh2 = npy_half_to_float(h2);
    float div, mod;

    div = npy_divmodf(fh1, fh2, &mod);
    *modulus = npy_float_to_half(mod);
    return npy_float_to_half(div);
}