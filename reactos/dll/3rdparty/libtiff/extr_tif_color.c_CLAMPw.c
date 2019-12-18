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

__attribute__((used)) static float CLAMPw(float v, float vmin, float vmax)
{
    if( v < vmin )
    {
        /* printf("%f clamped to %f\n", v, vmin); */
        return vmin;
    }
    if( v > vmax )
    {
        /* printf("%f clamped to %f\n", v, vmax); */
        return vmax;
    }
    return v;
}