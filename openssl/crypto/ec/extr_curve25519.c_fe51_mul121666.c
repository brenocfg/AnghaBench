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
typedef  int uint64_t ;
typedef  int u128 ;
typedef  int* fe51 ;

/* Variables and functions */
 int MASK51 ; 

__attribute__((used)) static void fe51_mul121666(fe51 h, fe51 f)
{
    u128 h0 = f[0] * (u128)121666;
    u128 h1 = f[1] * (u128)121666;
    u128 h2 = f[2] * (u128)121666;
    u128 h3 = f[3] * (u128)121666;
    u128 h4 = f[4] * (u128)121666;
    uint64_t g0, g1, g2, g3, g4;

    h3 += (uint64_t)(h2 >> 51); g2 = (uint64_t)h2 & MASK51;
    h1 += (uint64_t)(h0 >> 51); g0 = (uint64_t)h0 & MASK51;

    h4 += (uint64_t)(h3 >> 51); g3 = (uint64_t)h3 & MASK51;
    g2 += (uint64_t)(h1 >> 51); g1 = (uint64_t)h1 & MASK51;

    g0 += (uint64_t)(h4 >> 51) * 19; g4 = (uint64_t)h4 & MASK51;
    g3 += g2 >> 51; g2 &= MASK51;
    g1 += g0 >> 51; g0 &= MASK51;

    h[0] = g0;
    h[1] = g1;
    h[2] = g2;
    h[3] = g3;
    h[4] = g4;
}