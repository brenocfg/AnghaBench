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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int* fe51 ;

/* Variables and functions */
 int MASK51 ; 

__attribute__((used)) static void fe51_tobytes(uint8_t *s, const fe51 h)
{
    uint64_t h0 = h[0];
    uint64_t h1 = h[1];
    uint64_t h2 = h[2];
    uint64_t h3 = h[3];
    uint64_t h4 = h[4];
    uint64_t q;

    /* compare to modulus */
    q = (h0 + 19) >> 51;
    q = (h1 + q) >> 51;
    q = (h2 + q) >> 51;
    q = (h3 + q) >> 51;
    q = (h4 + q) >> 51;

    /* full reduce */
    h0 += 19 * q;
    h1 += h0 >> 51; h0 &= MASK51;
    h2 += h1 >> 51; h1 &= MASK51;
    h3 += h2 >> 51; h2 &= MASK51;
    h4 += h3 >> 51; h3 &= MASK51;
                    h4 &= MASK51;

    /* smash */
    s[0] = (uint8_t)(h0 >> 0);
    s[1] = (uint8_t)(h0 >> 8);
    s[2] = (uint8_t)(h0 >> 16);
    s[3] = (uint8_t)(h0 >> 24);
    s[4] = (uint8_t)(h0 >> 32);
    s[5] = (uint8_t)(h0 >> 40);
    s[6] = (uint8_t)((h0 >> 48) | ((uint32_t)h1 << 3));
    s[7] = (uint8_t)(h1 >> 5);
    s[8] = (uint8_t)(h1 >> 13);
    s[9] = (uint8_t)(h1 >> 21);
    s[10] = (uint8_t)(h1 >> 29);
    s[11] = (uint8_t)(h1 >> 37);
    s[12] = (uint8_t)((h1 >> 45) | ((uint32_t)h2 << 6));
    s[13] = (uint8_t)(h2 >> 2);
    s[14] = (uint8_t)(h2 >> 10);
    s[15] = (uint8_t)(h2 >> 18);
    s[16] = (uint8_t)(h2 >> 26);
    s[17] = (uint8_t)(h2 >> 34);
    s[18] = (uint8_t)(h2 >> 42);
    s[19] = (uint8_t)((h2 >> 50) | ((uint32_t)h3 << 1));
    s[20] = (uint8_t)(h3 >> 7);
    s[21] = (uint8_t)(h3 >> 15);
    s[22] = (uint8_t)(h3 >> 23);
    s[23] = (uint8_t)(h3 >> 31);
    s[24] = (uint8_t)(h3 >> 39);
    s[25] = (uint8_t)((h3 >> 47) | ((uint32_t)h4 << 4));
    s[26] = (uint8_t)(h4 >> 4);
    s[27] = (uint8_t)(h4 >> 12);
    s[28] = (uint8_t)(h4 >> 20);
    s[29] = (uint8_t)(h4 >> 28);
    s[30] = (uint8_t)(h4 >> 36);
    s[31] = (uint8_t)(h4 >> 44);
}