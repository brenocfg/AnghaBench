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

/* Variables and functions */

__attribute__((used)) static void pres_int_from_float(void *out, const void *in, unsigned int count)
{
    unsigned int i;
    const float *in_float = in;
    int *out_int = out;

    for (i = 0; i < count; ++i)
        out_int[i] = in_float[i];
}