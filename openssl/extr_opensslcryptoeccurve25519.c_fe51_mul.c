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

__attribute__((used)) static void fe51_mul(fe51 h, const fe51 f, const fe51 g)
{
    u128 h0, h1, h2, h3, h4;
    uint64_t f_i, g0, g1, g2, g3, g4;

    f_i = f[0];
    h0 = (u128)f_i * (g0 = g[0]);
    h1 = (u128)f_i * (g1 = g[1]);
    h2 = (u128)f_i * (g2 = g[2]);
    h3 = (u128)f_i * (g3 = g[3]);
    h4 = (u128)f_i * (g4 = g[4]);

    f_i = f[1];
    h0 += (u128)f_i * (g4 *= 19);
    h1 += (u128)f_i * g0;
    h2 += (u128)f_i * g1;
    h3 += (u128)f_i * g2;
    h4 += (u128)f_i * g3;

    f_i = f[2];
    h0 += (u128)f_i * (g3 *= 19);
    h1 += (u128)f_i * g4;
    h2 += (u128)f_i * g0;
    h3 += (u128)f_i * g1;
    h4 += (u128)f_i * g2;

    f_i = f[3];
    h0 += (u128)f_i * (g2 *= 19);
    h1 += (u128)f_i * g3;
    h2 += (u128)f_i * g4;
    h3 += (u128)f_i * g0;
    h4 += (u128)f_i * g1;

    f_i = f[4];
    h0 += (u128)f_i * (g1 *= 19);
    h1 += (u128)f_i * g2;
    h2 += (u128)f_i * g3;
    h3 += (u128)f_i * g4;
    h4 += (u128)f_i * g0;

    /* partial [lazy] reduction */
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