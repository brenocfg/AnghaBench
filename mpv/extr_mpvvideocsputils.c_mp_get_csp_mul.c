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
typedef  enum mp_csp { ____Placeholder_mp_csp } mp_csp ;

/* Variables and functions */
 int MP_CSP_RGB ; 
 int MP_CSP_XYZ ; 
 int /*<<< orphan*/  assert (int) ; 

double mp_get_csp_mul(enum mp_csp csp, int input_bits, int texture_bits)
{
    assert(texture_bits >= input_bits);

    // Convenience for some irrelevant cases, e.g. rgb565 or disabling expansion.
    if (!input_bits)
        return 1;

    // RGB always uses the full range available.
    if (csp == MP_CSP_RGB)
        return ((1LL << input_bits) - 1.) / ((1LL << texture_bits) - 1.);

    if (csp == MP_CSP_XYZ)
        return 1;

    // High bit depth YUV uses a range shifted from 8 bit.
    return (1LL << input_bits) / ((1LL << texture_bits) - 1.) * 255 / 256;
}