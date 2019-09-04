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
typedef  int /*<<< orphan*/  ctr ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 size_t ECDH_KDF_MAX ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 size_t EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

int ecdh_KDF_X9_63(unsigned char *out, size_t outlen,
                   const unsigned char *Z, size_t Zlen,
                   const unsigned char *sinfo, size_t sinfolen,
                   const EVP_MD *md)
{
    EVP_MD_CTX *mctx = NULL;
    int rv = 0;
    unsigned int i;
    size_t mdlen;
    unsigned char ctr[4];
    if (sinfolen > ECDH_KDF_MAX || outlen > ECDH_KDF_MAX
        || Zlen > ECDH_KDF_MAX)
        return 0;
    mctx = EVP_MD_CTX_new();
    if (mctx == NULL)
        return 0;
    mdlen = EVP_MD_size(md);
    for (i = 1;; i++) {
        unsigned char mtmp[EVP_MAX_MD_SIZE];
        if (!EVP_DigestInit_ex(mctx, md, NULL))
            goto err;
        ctr[3] = i & 0xFF;
        ctr[2] = (i >> 8) & 0xFF;
        ctr[1] = (i >> 16) & 0xFF;
        ctr[0] = (i >> 24) & 0xFF;
        if (!EVP_DigestUpdate(mctx, Z, Zlen))
            goto err;
        if (!EVP_DigestUpdate(mctx, ctr, sizeof(ctr)))
            goto err;
        if (!EVP_DigestUpdate(mctx, sinfo, sinfolen))
            goto err;
        if (outlen >= mdlen) {
            if (!EVP_DigestFinal(mctx, out, NULL))
                goto err;
            outlen -= mdlen;
            if (outlen == 0)
                break;
            out += mdlen;
        } else {
            if (!EVP_DigestFinal(mctx, mtmp, NULL))
                goto err;
            memcpy(out, mtmp, outlen);
            OPENSSL_cleanse(mtmp, mdlen);
            break;
        }
    }
    rv = 1;
 err:
    EVP_MD_CTX_free(mctx);
    return rv;
}