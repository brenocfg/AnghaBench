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
typedef  int /*<<< orphan*/  prev ;
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int HKDF_Expand(const EVP_MD *evp_md,
                       const unsigned char *prk, size_t prk_len,
                       const unsigned char *info, size_t info_len,
                       unsigned char *okm, size_t okm_len)
{
    HMAC_CTX *hmac;
    int ret = 0, sz;
    unsigned int i;
    unsigned char prev[EVP_MAX_MD_SIZE];
    size_t done_len = 0, dig_len, n;

    sz = EVP_MD_size(evp_md);
    if (sz <= 0)
        return 0;
    dig_len = (size_t)sz;

    /* calc: N = ceil(L/HashLen) */
    n = okm_len / dig_len;
    if (okm_len % dig_len)
        n++;

    if (n > 255 || okm == NULL)
        return 0;

    if ((hmac = HMAC_CTX_new()) == NULL)
        return 0;

    if (!HMAC_Init_ex(hmac, prk, prk_len, evp_md, NULL))
        goto err;

    for (i = 1; i <= n; i++) {
        size_t copy_len;
        const unsigned char ctr = i;

        /* calc: T(i) = HMAC-Hash(PRK, T(i - 1) | info | i) */
        if (i > 1) {
            if (!HMAC_Init_ex(hmac, NULL, 0, NULL, NULL))
                goto err;

            if (!HMAC_Update(hmac, prev, dig_len))
                goto err;
        }

        if (!HMAC_Update(hmac, info, info_len))
            goto err;

        if (!HMAC_Update(hmac, &ctr, 1))
            goto err;

        if (!HMAC_Final(hmac, prev, NULL))
            goto err;

        copy_len = (done_len + dig_len > okm_len) ?
                       okm_len - done_len :
                       dig_len;

        memcpy(okm + done_len, prev, copy_len);

        done_len += copy_len;
    }
    ret = 1;

 err:
    OPENSSL_cleanse(prev, sizeof(prev));
    HMAC_CTX_free(hmac);
    return ret;
}