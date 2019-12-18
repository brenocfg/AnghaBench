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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int* fe ;

/* Variables and functions */
 int kBottom25Bits ; 
 int kBottom26Bits ; 

__attribute__((used)) static void fe_tobytes(uint8_t *s, const fe h)
{
    int32_t h0 = h[0];
    int32_t h1 = h[1];
    int32_t h2 = h[2];
    int32_t h3 = h[3];
    int32_t h4 = h[4];
    int32_t h5 = h[5];
    int32_t h6 = h[6];
    int32_t h7 = h[7];
    int32_t h8 = h[8];
    int32_t h9 = h[9];
    int32_t q;

    q = (19 * h9 + (((int32_t) 1) << 24)) >> 25;
    q = (h0 + q) >> 26;
    q = (h1 + q) >> 25;
    q = (h2 + q) >> 26;
    q = (h3 + q) >> 25;
    q = (h4 + q) >> 26;
    q = (h5 + q) >> 25;
    q = (h6 + q) >> 26;
    q = (h7 + q) >> 25;
    q = (h8 + q) >> 26;
    q = (h9 + q) >> 25;

    /* Goal: Output h-(2^255-19)q, which is between 0 and 2^255-20. */
    h0 += 19 * q;
    /* Goal: Output h-2^255 q, which is between 0 and 2^255-20. */

    h1 += h0 >> 26; h0 &= kBottom26Bits;
    h2 += h1 >> 25; h1 &= kBottom25Bits;
    h3 += h2 >> 26; h2 &= kBottom26Bits;
    h4 += h3 >> 25; h3 &= kBottom25Bits;
    h5 += h4 >> 26; h4 &= kBottom26Bits;
    h6 += h5 >> 25; h5 &= kBottom25Bits;
    h7 += h6 >> 26; h6 &= kBottom26Bits;
    h8 += h7 >> 25; h7 &= kBottom25Bits;
    h9 += h8 >> 26; h8 &= kBottom26Bits;
                    h9 &= kBottom25Bits;
    /* h10 = carry9 */

    /*
     * Goal: Output h0+...+2^255 h10-2^255 q, which is between 0 and 2^255-20.
     * Have h0+...+2^230 h9 between 0 and 2^255-1;
     * evidently 2^255 h10-2^255 q = 0.
     * Goal: Output h0+...+2^230 h9.
     */
    s[ 0] = (uint8_t) (h0 >>  0);
    s[ 1] = (uint8_t) (h0 >>  8);
    s[ 2] = (uint8_t) (h0 >> 16);
    s[ 3] = (uint8_t)((h0 >> 24) | ((uint32_t)(h1) << 2));
    s[ 4] = (uint8_t) (h1 >>  6);
    s[ 5] = (uint8_t) (h1 >> 14);
    s[ 6] = (uint8_t)((h1 >> 22) | ((uint32_t)(h2) << 3));
    s[ 7] = (uint8_t) (h2 >>  5);
    s[ 8] = (uint8_t) (h2 >> 13);
    s[ 9] = (uint8_t)((h2 >> 21) | ((uint32_t)(h3) << 5));
    s[10] = (uint8_t) (h3 >>  3);
    s[11] = (uint8_t) (h3 >> 11);
    s[12] = (uint8_t)((h3 >> 19) | ((uint32_t)(h4) << 6));
    s[13] = (uint8_t) (h4 >>  2);
    s[14] = (uint8_t) (h4 >> 10);
    s[15] = (uint8_t) (h4 >> 18);
    s[16] = (uint8_t) (h5 >>  0);
    s[17] = (uint8_t) (h5 >>  8);
    s[18] = (uint8_t) (h5 >> 16);
    s[19] = (uint8_t)((h5 >> 24) | ((uint32_t)(h6) << 1));
    s[20] = (uint8_t) (h6 >>  7);
    s[21] = (uint8_t) (h6 >> 15);
    s[22] = (uint8_t)((h6 >> 23) | ((uint32_t)(h7) << 3));
    s[23] = (uint8_t) (h7 >>  5);
    s[24] = (uint8_t) (h7 >> 13);
    s[25] = (uint8_t)((h7 >> 21) | ((uint32_t)(h8) << 4));
    s[26] = (uint8_t) (h8 >>  4);
    s[27] = (uint8_t) (h8 >> 12);
    s[28] = (uint8_t)((h8 >> 20) | ((uint32_t)(h9) << 6));
    s[29] = (uint8_t) (h9 >>  2);
    s[30] = (uint8_t) (h9 >> 10);
    s[31] = (uint8_t) (h9 >> 18);
}