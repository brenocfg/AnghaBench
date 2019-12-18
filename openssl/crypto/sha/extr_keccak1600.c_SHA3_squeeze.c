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
typedef  int /*<<< orphan*/  A ;

/* Variables and functions */
 int BitDeinterleave (int) ; 
 int /*<<< orphan*/  KeccakF1600 (int**) ; 
 int /*<<< orphan*/  assert (int) ; 

void SHA3_squeeze(uint64_t A[5][5], unsigned char *out, size_t len, size_t r)
{
    uint64_t *A_flat = (uint64_t *)A;
    size_t i, w = r / 8;

    assert(r < (25 * sizeof(A[0][0])) && (r % 8) == 0);

    while (len != 0) {
        for (i = 0; i < w && len != 0; i++) {
            uint64_t Ai = BitDeinterleave(A_flat[i]);

            if (len < 8) {
                for (i = 0; i < len; i++) {
                    *out++ = (unsigned char)Ai;
                    Ai >>= 8;
                }
                return;
            }

            out[0] = (unsigned char)(Ai);
            out[1] = (unsigned char)(Ai >> 8);
            out[2] = (unsigned char)(Ai >> 16);
            out[3] = (unsigned char)(Ai >> 24);
            out[4] = (unsigned char)(Ai >> 32);
            out[5] = (unsigned char)(Ai >> 40);
            out[6] = (unsigned char)(Ai >> 48);
            out[7] = (unsigned char)(Ai >> 56);
            out += 8;
            len -= 8;
        }
        if (len)
            KeccakF1600(A);
    }
}