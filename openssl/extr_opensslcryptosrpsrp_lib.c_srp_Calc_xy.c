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
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int SHA_DIGEST_LENGTH ; 

__attribute__((used)) static BIGNUM *srp_Calc_xy(const BIGNUM *x, const BIGNUM *y, const BIGNUM *N)
{
    unsigned char digest[SHA_DIGEST_LENGTH];
    unsigned char *tmp = NULL;
    int numN = BN_num_bytes(N);
    BIGNUM *res = NULL;

    if (x != N && BN_ucmp(x, N) >= 0)
        return NULL;
    if (y != N && BN_ucmp(y, N) >= 0)
        return NULL;
    if ((tmp = OPENSSL_malloc(numN * 2)) == NULL)
        goto err;
    if (BN_bn2binpad(x, tmp, numN) < 0
        || BN_bn2binpad(y, tmp + numN, numN) < 0
        || !EVP_Digest(tmp, numN * 2, digest, NULL, EVP_sha1(), NULL))
        goto err;
    res = BN_bin2bn(digest, sizeof(digest), NULL);
 err:
    OPENSSL_free(tmp);
    return res;
}