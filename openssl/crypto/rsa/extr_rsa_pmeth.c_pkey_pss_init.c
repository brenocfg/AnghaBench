#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* pkey; TYPE_3__* data; } ;
struct TYPE_13__ {int /*<<< orphan*/ * pss; } ;
struct TYPE_12__ {int min_saltlen; int saltlen; int /*<<< orphan*/  const* mgf1md; int /*<<< orphan*/  const* md; } ;
struct TYPE_10__ {TYPE_4__* rsa; } ;
struct TYPE_11__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ RSA_PKEY_CTX ;
typedef  TYPE_4__ RSA ;
typedef  TYPE_5__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RSA_F_PKEY_PSS_INIT ; 
 int /*<<< orphan*/  RSA_R_INVALID_SALT_LENGTH ; 
 int RSA_bits (TYPE_4__*) ; 
 int RSA_size (TYPE_4__*) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_ctx_is_pss (TYPE_5__*) ; 
 int /*<<< orphan*/  rsa_pss_get_param (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int pkey_pss_init(EVP_PKEY_CTX *ctx)
{
    RSA *rsa;
    RSA_PKEY_CTX *rctx = ctx->data;
    const EVP_MD *md;
    const EVP_MD *mgf1md;
    int min_saltlen, max_saltlen;

    /* Should never happen */
    if (!pkey_ctx_is_pss(ctx))
        return 0;
    rsa = ctx->pkey->pkey.rsa;
    /* If no restrictions just return */
    if (rsa->pss == NULL)
        return 1;
    /* Get and check parameters */
    if (!rsa_pss_get_param(rsa->pss, &md, &mgf1md, &min_saltlen))
        return 0;

    /* See if minimum salt length exceeds maximum possible */
    max_saltlen = RSA_size(rsa) - EVP_MD_size(md);
    if ((RSA_bits(rsa) & 0x7) == 1)
        max_saltlen--;
    if (min_saltlen > max_saltlen) {
        RSAerr(RSA_F_PKEY_PSS_INIT, RSA_R_INVALID_SALT_LENGTH);
        return 0;
    }

    rctx->min_saltlen = min_saltlen;

    /*
     * Set PSS restrictions as defaults: we can then block any attempt to
     * use invalid values in pkey_rsa_ctrl
     */

    rctx->md = md;
    rctx->mgf1md = mgf1md;
    rctx->saltlen = min_saltlen;

    return 1;
}