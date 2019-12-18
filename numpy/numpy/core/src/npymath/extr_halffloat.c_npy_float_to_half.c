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
 int /*<<< orphan*/  npy_floatbits_to_halfbits (int /*<<< orphan*/ ) ; 

npy_half npy_float_to_half(float f)
{
    union { float f; npy_uint32 fbits; } conv;
    conv.f = f;
    return npy_floatbits_to_halfbits(conv.fbits);
}