#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  nid; } ;
typedef  TYPE_1__ TLS_GROUP_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_dh_nid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_ec_paramgen_curve_nid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_DH ; 
 int EVP_PKEY_EC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 scalar_t__ EVP_PKEY_paramgen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_paramgen_init (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TLS_GROUP_CURVE_CUSTOM ; 
 int TLS_GROUP_FFDHE ; 
 int TLS_GROUP_TYPE ; 
 TYPE_1__* tls1_group_id_lookup (int /*<<< orphan*/ ) ; 

EVP_PKEY *ssl_generate_param_group(uint16_t id)
{
    EVP_PKEY_CTX *pctx = NULL;
    EVP_PKEY *pkey = NULL;
    const TLS_GROUP_INFO *ginf = tls1_group_id_lookup(id);
    int pkey_ctx_id;

    if (ginf == NULL)
        goto err;

    if ((ginf->flags & TLS_GROUP_TYPE) == TLS_GROUP_CURVE_CUSTOM) {
        pkey = EVP_PKEY_new();
        if (pkey != NULL && EVP_PKEY_set_type(pkey, ginf->nid))
            return pkey;
        EVP_PKEY_free(pkey);
        return NULL;
    }

    pkey_ctx_id = (ginf->flags & TLS_GROUP_FFDHE)
                        ? EVP_PKEY_DH : EVP_PKEY_EC;
    pctx = EVP_PKEY_CTX_new_id(pkey_ctx_id, NULL);
    if (pctx == NULL)
        goto err;
    if (EVP_PKEY_paramgen_init(pctx) <= 0)
        goto err;
# ifndef OPENSSL_NO_DH
    if (ginf->flags & TLS_GROUP_FFDHE) {
        if (EVP_PKEY_CTX_set_dh_nid(pctx, ginf->nid) <= 0)
            goto err;
    }
#  ifndef OPENSSL_NO_EC
    else
#  endif
# endif
# ifndef OPENSSL_NO_EC
    {
        if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, ginf->nid) <= 0)
            goto err;
    }
# endif
    if (EVP_PKEY_paramgen(pctx, &pkey) <= 0) {
        EVP_PKEY_free(pkey);
        pkey = NULL;
    }

 err:
    EVP_PKEY_CTX_free(pctx);
    return pkey;
}