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
typedef  int /*<<< orphan*/  (* block128_f ) (unsigned char const*,unsigned char*,void*) ;

/* Variables and functions */
 size_t CRYPTO128_WRAP_MAX ; 
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 size_t crypto_128_unwrap_raw (void*,unsigned char*,unsigned char*,unsigned char const*,size_t,int /*<<< orphan*/  (*) (unsigned char const*,unsigned char*,void*)) ; 
 unsigned char* default_aiv ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

size_t CRYPTO_128_unwrap_pad(void *key, const unsigned char *icv,
                             unsigned char *out,
                             const unsigned char *in, size_t inlen,
                             block128_f block)
{
    /* n: number of 64-bit blocks in the padded key data */
    size_t n = inlen / 8 - 1;
    size_t padded_len;
    size_t padding_len;
    size_t ptext_len;
    /* RFC 5649 section 3: Alternative Initial Value */
    unsigned char aiv[8];
    static unsigned char zeros[8] = { 0x0 };
    size_t ret;

    /* Section 4.2: Ciphertext length has to be (n+1) 64-bit blocks. */
    if ((inlen & 0x7) != 0 || inlen < 16 || inlen >= CRYPTO128_WRAP_MAX)
        return 0;

    if (inlen == 16) {
        /*
         * Section 4.2 - special case in step 1: When n=1, the ciphertext
         * contains exactly two 64-bit blocks and they are decrypted as a
         * single AES block using AES in ECB mode: AIV | P[1] = DEC(K, C[0] |
         * C[1])
         */
        unsigned char buff[16];

        block(in, buff, key);
        memcpy(aiv, buff, 8);
        /* Remove AIV */
        memcpy(out, buff + 8, 8);
        padded_len = 8;
        OPENSSL_cleanse(buff, inlen);
    } else {
        padded_len = inlen - 8;
        ret = crypto_128_unwrap_raw(key, aiv, out, in, inlen, block);
        if (padded_len != ret) {
            OPENSSL_cleanse(out, inlen);
            return 0;
        }
    }

    /*
     * Section 3: AIV checks: Check that MSB(32,A) = A65959A6. Optionally a
     * user-supplied value can be used (even if standard doesn't mention
     * this).
     */
    if ((!icv && CRYPTO_memcmp(aiv, default_aiv, 4))
        || (icv && CRYPTO_memcmp(aiv, icv, 4))) {
        OPENSSL_cleanse(out, inlen);
        return 0;
    }

    /*
     * Check that 8*(n-1) < LSB(32,AIV) <= 8*n. If so, let ptext_len =
     * LSB(32,AIV).
     */

    ptext_len =   ((unsigned int)aiv[4] << 24)
                | ((unsigned int)aiv[5] << 16)
                | ((unsigned int)aiv[6] <<  8)
                |  (unsigned int)aiv[7];
    if (8 * (n - 1) >= ptext_len || ptext_len > 8 * n) {
        OPENSSL_cleanse(out, inlen);
        return 0;
    }

    /*
     * Check that the rightmost padding_len octets of the output data are
     * zero.
     */
    padding_len = padded_len - ptext_len;
    if (CRYPTO_memcmp(out + ptext_len, zeros, padding_len) != 0) {
        OPENSSL_cleanse(out, inlen);
        return 0;
    }

    /* Section 4.2 step 3: Remove padding */
    return ptext_len;
}