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
 float copysignf (float,float) ; 
 scalar_t__ isfinite (float) ; 
 int /*<<< orphan*/  sprintf (char*,char*,float) ; 

void wined3d_ftoa(float value, char *s)
{
    int idx = 1;

    if (copysignf(1.0f, value) < 0.0f)
        ++idx;

    /* Be sure to allocate a buffer of at least 17 characters for the result
       as sprintf may return a 3 digit exponent when using the MSVC runtime
       instead of a 2 digit exponent. */
    sprintf(s, "%.8e", value);
    if (isfinite(value))
        s[idx] = '.';
}