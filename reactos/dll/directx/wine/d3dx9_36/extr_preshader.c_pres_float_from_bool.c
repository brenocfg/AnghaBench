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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */

__attribute__((used)) static void pres_float_from_bool(void *out, const void *in, unsigned int count)
{
    unsigned int i;
    const BOOL *in_bool = in;
    float *out_float = out;

    for (i = 0; i < count; ++i)
        out_float[i] = !!in_bool[i];
}