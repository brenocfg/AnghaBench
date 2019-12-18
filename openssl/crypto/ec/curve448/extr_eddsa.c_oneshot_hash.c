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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  c448_error_t ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  C448_FAILURE ; 
 int /*<<< orphan*/  C448_SUCCESS ; 
 int /*<<< orphan*/  EVP_DigestFinalXOF (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static c448_error_t oneshot_hash(OPENSSL_CTX *ctx, uint8_t *out, size_t outlen,
                                 const uint8_t *in, size_t inlen)
{
    EVP_MD_CTX *hashctx = EVP_MD_CTX_new();
    EVP_MD *shake256 = NULL;
    c448_error_t ret = C448_FAILURE;

    if (hashctx == NULL)
        return C448_FAILURE;

    shake256 = EVP_MD_fetch(ctx, "SHAKE256", NULL);
    if (shake256 == NULL)
        goto err;

    if (!EVP_DigestInit_ex(hashctx, shake256, NULL)
            || !EVP_DigestUpdate(hashctx, in, inlen)
            || !EVP_DigestFinalXOF(hashctx, out, outlen))
        goto err;

    ret = C448_SUCCESS;
 err:
    EVP_MD_CTX_free(hashctx);
    EVP_MD_free(shake256);
    return ret;
}