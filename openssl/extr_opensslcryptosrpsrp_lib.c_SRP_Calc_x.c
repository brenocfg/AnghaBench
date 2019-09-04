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
typedef  int /*<<< orphan*/  dig ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2bin (int /*<<< orphan*/  const*,unsigned char*) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int SHA_DIGEST_LENGTH ; 
 int strlen (char const*) ; 

BIGNUM *SRP_Calc_x(const BIGNUM *s, const char *user, const char *pass)
{
    unsigned char dig[SHA_DIGEST_LENGTH];
    EVP_MD_CTX *ctxt;
    unsigned char *cs = NULL;
    BIGNUM *res = NULL;

    if ((s == NULL) || (user == NULL) || (pass == NULL))
        return NULL;

    ctxt = EVP_MD_CTX_new();
    if (ctxt == NULL)
        return NULL;
    if ((cs = OPENSSL_malloc(BN_num_bytes(s))) == NULL)
        goto err;

    if (!EVP_DigestInit_ex(ctxt, EVP_sha1(), NULL)
        || !EVP_DigestUpdate(ctxt, user, strlen(user))
        || !EVP_DigestUpdate(ctxt, ":", 1)
        || !EVP_DigestUpdate(ctxt, pass, strlen(pass))
        || !EVP_DigestFinal_ex(ctxt, dig, NULL)
        || !EVP_DigestInit_ex(ctxt, EVP_sha1(), NULL))
        goto err;
    if (BN_bn2bin(s, cs) < 0)
        goto err;
    if (!EVP_DigestUpdate(ctxt, cs, BN_num_bytes(s)))
        goto err;

    if (!EVP_DigestUpdate(ctxt, dig, sizeof(dig))
        || !EVP_DigestFinal_ex(ctxt, dig, NULL))
        goto err;

    res = BN_bin2bn(dig, sizeof(dig), NULL);

 err:
    OPENSSL_free(cs);
    EVP_MD_CTX_free(ctxt);
    return res;
}