#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * gen_group; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pkey; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ EC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_PKEY_EC_KEYGEN ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int EC_KEY_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new () ; 
 int EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_NO_PARAMETERS_SET ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_copy_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_ec_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    EC_KEY *ec = NULL;
    EC_PKEY_CTX *dctx = ctx->data;
    int ret;

    if (ctx->pkey == NULL && dctx->gen_group == NULL) {
        ECerr(EC_F_PKEY_EC_KEYGEN, EC_R_NO_PARAMETERS_SET);
        return 0;
    }
    ec = EC_KEY_new();
    if (ec == NULL)
        return 0;
    if (!ossl_assert(EVP_PKEY_assign_EC_KEY(pkey, ec))) {
        EC_KEY_free(ec);
        return 0;
    }
    /* Note: if error is returned, we count on caller to free pkey->pkey.ec */
    if (ctx->pkey != NULL)
        ret = EVP_PKEY_copy_parameters(pkey, ctx->pkey);
    else
        ret = EC_KEY_set_group(ec, dctx->gen_group);

    return ret ? EC_KEY_generate_key(ec) : 0;
}