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
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 size_t crypto_128_unwrap_raw (void*,unsigned char*,unsigned char*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 unsigned char* default_iv ; 

size_t CRYPTO_128_unwrap(void *key, const unsigned char *iv,
                         unsigned char *out, const unsigned char *in,
                         size_t inlen, block128_f block)
{
    size_t ret;
    unsigned char got_iv[8];

    ret = crypto_128_unwrap_raw(key, got_iv, out, in, inlen, block);
    if (ret == 0)
        return 0;

    if (!iv)
        iv = default_iv;
    if (CRYPTO_memcmp(got_iv, iv, 8)) {
        OPENSSL_cleanse(out, ret);
        return 0;
    }
    return ret;
}