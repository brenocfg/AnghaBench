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
 float MPMAX (float,float) ; 
 float MPMIN (float,float) ; 
 int /*<<< orphan*/  assert (int) ; 
 float log10 (float) ; 

float gl_video_scale_ambient_lux(float lmin, float lmax,
                                 float rmin, float rmax, float lux)
{
    assert(lmax > lmin);

    float num = (rmax - rmin) * (log10(lux) - log10(lmin));
    float den = log10(lmax) - log10(lmin);
    float result = num / den + rmin;

    // clamp the result
    float max = MPMAX(rmax, rmin);
    float min = MPMIN(rmax, rmin);
    return MPMAX(MPMIN(result, max), min);
}