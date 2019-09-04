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
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  int /*<<< orphan*/  npy_half ;

/* Variables and functions */
 int /*<<< orphan*/  npy_halfbits_to_floatbits (int /*<<< orphan*/ ) ; 

float npy_half_to_float(npy_half h)
{
    union { float ret; npy_uint32 retbits; } conv;
    conv.retbits = npy_halfbits_to_floatbits(h);
    return conv.ret;
}