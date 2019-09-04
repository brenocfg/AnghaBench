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
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HMAC_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int pkcs5_pbkdf2_alg(const char *pass, size_t passlen,
                            const unsigned char *salt, int saltlen, int iter,
                            const EVP_MD *digest, unsigned char *key,
                            size_t keylen)
{
    int ret = 0;
    unsigned char digtmp[EVP_MAX_MD_SIZE], *p, itmp[4];
    int cplen, j, k, tkeylen, mdlen;
    unsigned long i = 1;
    HMAC_CTX *hctx_tpl = NULL, *hctx = NULL;

    mdlen = EVP_MD_size(digest);
    if (mdlen < 0)
        return 0;

    hctx_tpl = HMAC_CTX_new();
    if (hctx_tpl == NULL)
        return 0;
    p = key;
    tkeylen = keylen;
    if (!HMAC_Init_ex(hctx_tpl, pass, passlen, digest, NULL))
        goto err;
    hctx = HMAC_CTX_new();
    if (hctx == NULL)
        goto err;
    while (tkeylen) {
        if (tkeylen > mdlen)
            cplen = mdlen;
        else
            cplen = tkeylen;
        /*
         * We are unlikely to ever use more than 256 blocks (5120 bits!) but
         * just in case...
         */
        itmp[0] = (unsigned char)((i >> 24) & 0xff);
        itmp[1] = (unsigned char)((i >> 16) & 0xff);
        itmp[2] = (unsigned char)((i >> 8) & 0xff);
        itmp[3] = (unsigned char)(i & 0xff);
        if (!HMAC_CTX_copy(hctx, hctx_tpl))
            goto err;
        if (!HMAC_Update(hctx, salt, saltlen)
                || !HMAC_Update(hctx, itmp, 4)
                || !HMAC_Final(hctx, digtmp, NULL))
            goto err;
        memcpy(p, digtmp, cplen);
        for (j = 1; j < iter; j++) {
            if (!HMAC_CTX_copy(hctx, hctx_tpl))
                goto err;
            if (!HMAC_Update(hctx, digtmp, mdlen)
                    || !HMAC_Final(hctx, digtmp, NULL))
                goto err;
            for (k = 0; k < cplen; k++)
                p[k] ^= digtmp[k];
        }
        tkeylen -= cplen;
        i++;
        p += cplen;
    }
    ret = 1;

err:
    HMAC_CTX_free(hctx);
    HMAC_CTX_free(hctx_tpl);
    return ret;
}