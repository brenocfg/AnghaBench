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
typedef  int /*<<< orphan*/  (* block128_f ) (unsigned char*,unsigned char*,void const*) ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub4 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub5 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub6 (unsigned char*,unsigned char*,void const*) ; 

void CRYPTO_cfb128_encrypt(const unsigned char *in, unsigned char *out,
                           size_t len, const void *key,
                           unsigned char ivec[16], int *num,
                           int enc, block128_f block)
{
    unsigned int n;
    size_t l = 0;

    n = *num;

    if (enc) {
#if !defined(OPENSSL_SMALL_FOOTPRINT)
        if (16 % sizeof(size_t) == 0) { /* always true actually */
            do {
                while (n && len) {
                    *(out++) = ivec[n] ^= *(in++);
                    --len;
                    n = (n + 1) % 16;
                }
# if defined(STRICT_ALIGNMENT)
                if (((size_t)in | (size_t)out | (size_t)ivec) %
                    sizeof(size_t) != 0)
                    break;
# endif
                while (len >= 16) {
                    (*block) (ivec, ivec, key);
                    for (; n < 16; n += sizeof(size_t)) {
                        *(size_t *)(out + n) =
                            *(size_t *)(ivec + n) ^= *(size_t *)(in + n);
                    }
                    len -= 16;
                    out += 16;
                    in += 16;
                    n = 0;
                }
                if (len) {
                    (*block) (ivec, ivec, key);
                    while (len--) {
                        out[n] = ivec[n] ^= in[n];
                        ++n;
                    }
                }
                *num = n;
                return;
            } while (0);
        }
        /* the rest would be commonly eliminated by x86* compiler */
#endif
        while (l < len) {
            if (n == 0) {
                (*block) (ivec, ivec, key);
            }
            out[l] = ivec[n] ^= in[l];
            ++l;
            n = (n + 1) % 16;
        }
        *num = n;
    } else {
#if !defined(OPENSSL_SMALL_FOOTPRINT)
        if (16 % sizeof(size_t) == 0) { /* always true actually */
            do {
                while (n && len) {
                    unsigned char c;
                    *(out++) = ivec[n] ^ (c = *(in++));
                    ivec[n] = c;
                    --len;
                    n = (n + 1) % 16;
                }
# if defined(STRICT_ALIGNMENT)
                if (((size_t)in | (size_t)out | (size_t)ivec) %
                    sizeof(size_t) != 0)
                    break;
# endif
                while (len >= 16) {
                    (*block) (ivec, ivec, key);
                    for (; n < 16; n += sizeof(size_t)) {
                        size_t t = *(size_t *)(in + n);
                        *(size_t *)(out + n) = *(size_t *)(ivec + n) ^ t;
                        *(size_t *)(ivec + n) = t;
                    }
                    len -= 16;
                    out += 16;
                    in += 16;
                    n = 0;
                }
                if (len) {
                    (*block) (ivec, ivec, key);
                    while (len--) {
                        unsigned char c;
                        out[n] = ivec[n] ^ (c = in[n]);
                        ivec[n] = c;
                        ++n;
                    }
                }
                *num = n;
                return;
            } while (0);
        }
        /* the rest would be commonly eliminated by x86* compiler */
#endif
        while (l < len) {
            unsigned char c;
            if (n == 0) {
                (*block) (ivec, ivec, key);
            }
            out[l] = ivec[n] ^ (c = in[l]);
            ivec[n] = c;
            ++l;
            n = (n + 1) % 16;
        }
        *num = n;
    }
}