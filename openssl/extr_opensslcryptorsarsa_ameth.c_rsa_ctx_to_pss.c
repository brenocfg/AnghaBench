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
typedef  int /*<<< orphan*/  RSA_PSS_PARAMS ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_get_rsa_mgf1_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_get_rsa_pss_saltlen (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ EVP_PKEY_CTX_get_signature_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int EVP_PKEY_bits (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rsa_pss_params_create (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static RSA_PSS_PARAMS *rsa_ctx_to_pss(EVP_PKEY_CTX *pkctx)
{
    const EVP_MD *sigmd, *mgf1md;
    EVP_PKEY *pk = EVP_PKEY_CTX_get0_pkey(pkctx);
    int saltlen;

    if (EVP_PKEY_CTX_get_signature_md(pkctx, &sigmd) <= 0)
        return NULL;
    if (EVP_PKEY_CTX_get_rsa_mgf1_md(pkctx, &mgf1md) <= 0)
        return NULL;
    if (!EVP_PKEY_CTX_get_rsa_pss_saltlen(pkctx, &saltlen))
        return NULL;
    if (saltlen == -1) {
        saltlen = EVP_MD_size(sigmd);
    } else if (saltlen == -2 || saltlen == -3) {
        saltlen = EVP_PKEY_size(pk) - EVP_MD_size(sigmd) - 2;
        if ((EVP_PKEY_bits(pk) & 0x7) == 1)
            saltlen--;
        if (saltlen < 0)
            return NULL;
    }

    return rsa_pss_params_create(sigmd, mgf1md, saltlen);
}