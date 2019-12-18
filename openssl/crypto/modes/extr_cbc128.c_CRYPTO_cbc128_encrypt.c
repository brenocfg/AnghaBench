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
 scalar_t__ STRICT_ALIGNMENT ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char*,void const*) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,unsigned char*,void const*) ; 

void CRYPTO_cbc128_encrypt(const unsigned char *in, unsigned char *out,
                           size_t len, const void *key,
                           unsigned char ivec[16], block128_f block)
{
    size_t n;
    const unsigned char *iv = ivec;

    if (len == 0)
        return;

#if !defined(OPENSSL_SMALL_FOOTPRINT)
    if (STRICT_ALIGNMENT &&
        ((size_t)in | (size_t)out | (size_t)ivec) % sizeof(size_t) != 0) {
        while (len >= 16) {
            for (n = 0; n < 16; ++n)
                out[n] = in[n] ^ iv[n];
            (*block) (out, out, key);
            iv = out;
            len -= 16;
            in += 16;
            out += 16;
        }
    } else {
        while (len >= 16) {
            for (n = 0; n < 16; n += sizeof(size_t))
                *(size_t *)(out + n) =
                    *(size_t *)(in + n) ^ *(size_t *)(iv + n);
            (*block) (out, out, key);
            iv = out;
            len -= 16;
            in += 16;
            out += 16;
        }
    }
#endif
    while (len) {
        for (n = 0; n < 16 && n < len; ++n)
            out[n] = in[n] ^ iv[n];
        for (; n < 16; ++n)
            out[n] = iv[n];
        (*block) (out, out, key);
        iv = out;
        if (len <= 16)
            break;
        len -= 16;
        in += 16;
        out += 16;
    }
    memcpy(ivec, iv, 16);
}