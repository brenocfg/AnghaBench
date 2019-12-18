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
 float const INFINITY ; 
 float NAN ; 
 float const powf (int,float) ; 

__attribute__((used)) static inline float float_16_to_32(const unsigned short *in)
{
    const unsigned short s = ((*in) & 0x8000u);
    const unsigned short e = ((*in) & 0x7c00u) >> 10;
    const unsigned short m = (*in) & 0x3ffu;
    const float sgn = (s ? -1.0f : 1.0f);

    if(e == 0) {
        if(m == 0) return sgn * 0.0f; /* +0.0 or -0.0 */
        else return sgn * powf(2, -14.0f) * ((float)m / 1024.0f);
    } else if(e < 31) {
        return sgn * powf(2, (float)e - 15.0f) * (1.0f + ((float)m / 1024.0f));
    } else {
        if(m == 0) return sgn * INFINITY;
        else return NAN;
    }
}