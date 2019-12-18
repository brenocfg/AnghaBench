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
typedef  int /*<<< orphan*/  (* block128_f ) (unsigned char*,unsigned char*,void*) ;

/* Variables and functions */
 size_t CRYPTO128_WRAP_MAX ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static size_t crypto_128_unwrap_raw(void *key, unsigned char *iv,
                                    unsigned char *out,
                                    const unsigned char *in, size_t inlen,
                                    block128_f block)
{
    unsigned char *A, B[16], *R;
    size_t i, j, t;
    inlen -= 8;
    if ((inlen & 0x7) || (inlen < 16) || (inlen > CRYPTO128_WRAP_MAX))
        return 0;
    A = B;
    t = 6 * (inlen >> 3);
    memcpy(A, in, 8);
    memmove(out, in + 8, inlen);
    for (j = 0; j < 6; j++) {
        R = out + inlen - 8;
        for (i = 0; i < inlen; i += 8, t--, R -= 8) {
            A[7] ^= (unsigned char)(t & 0xff);
            if (t > 0xff) {
                A[6] ^= (unsigned char)((t >> 8) & 0xff);
                A[5] ^= (unsigned char)((t >> 16) & 0xff);
                A[4] ^= (unsigned char)((t >> 24) & 0xff);
            }
            memcpy(B + 8, R, 8);
            block(B, B, key);
            memcpy(R, B + 8, 8);
        }
    }
    memcpy(iv, A, 8);
    return inlen;
}