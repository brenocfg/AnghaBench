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
typedef  int /*<<< orphan*/  block128_f ;

/* Variables and functions */
 int /*<<< orphan*/  cfbr_encrypt_block (unsigned char*,unsigned char*,int,void const*,unsigned char*,int,int /*<<< orphan*/ ) ; 

void CRYPTO_cfb128_1_encrypt(const unsigned char *in, unsigned char *out,
                             size_t bits, const void *key,
                             unsigned char ivec[16], int *num,
                             int enc, block128_f block)
{
    size_t n;
    unsigned char c[1], d[1];

    for (n = 0; n < bits; ++n) {
        c[0] = (in[n / 8] & (1 << (7 - n % 8))) ? 0x80 : 0;
        cfbr_encrypt_block(c, d, 1, key, ivec, enc, block);
        out[n / 8] = (out[n / 8] & ~(1 << (unsigned int)(7 - n % 8))) |
            ((d[0] & 0x80) >> (unsigned int)(n % 8));
    }
}