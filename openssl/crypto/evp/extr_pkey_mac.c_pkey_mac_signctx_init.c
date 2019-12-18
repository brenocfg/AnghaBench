#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_1__* pmeth; } ;
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/  ctx; } ;
struct TYPE_10__ {int flags; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_2__ MAC_PKEY_CTX ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_4__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTX_mac (int /*<<< orphan*/ ) ; 
 int EVP_MAC_CTX_set_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_is_a (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NO_INIT ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_update_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_MD_CTX_test_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_get0_pkey (TYPE_3__*) ; 
 TYPE_2__* EVP_PKEY_CTX_get_data (TYPE_3__*) ; 
 int EVP_PKEY_FLAG_SIGCTX_CUSTOM ; 
 TYPE_4__* EVP_PKEY_get0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_id (int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_TYPE_RAW ; 
 int /*<<< orphan*/  OBJ_nid2sn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_FLAGS ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_int (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_update ; 

__attribute__((used)) static int pkey_mac_signctx_init(EVP_PKEY_CTX *ctx, EVP_MD_CTX *mctx)
{
    MAC_PKEY_CTX *hctx = EVP_PKEY_CTX_get_data(ctx);
    ASN1_OCTET_STRING *key = NULL;
    int rv = 1;
    /*
     * For MACs with the EVP_PKEY_FLAG_SIGCTX_CUSTOM flag set and that
     * gets the key passed as an ASN.1 OCTET STRING, we set the key here,
     * as this may be only time it's set during a DigestSign.
     *
     * MACs that pass around the key in form of EVP_MAC_CTX are setting
     * the key through other mechanisms.  (this is only CMAC for now)
     */
    int set_key =
        hctx->type == MAC_TYPE_RAW
        && (ctx->pmeth->flags & EVP_PKEY_FLAG_SIGCTX_CUSTOM) != 0;

    if (set_key) {
        if (!EVP_MAC_is_a(EVP_MAC_CTX_mac(hctx->ctx),
                          OBJ_nid2sn(EVP_PKEY_id(EVP_PKEY_CTX_get0_pkey(ctx)))))
            return 0;
        key = EVP_PKEY_get0(EVP_PKEY_CTX_get0_pkey(ctx));
        if (key == NULL)
            return 0;
    }

    EVP_MD_CTX_set_flags(mctx, EVP_MD_CTX_FLAG_NO_INIT);
    EVP_MD_CTX_set_update_fn(mctx, int_update);

    /* Some MACs don't support this control...  that's fine */
    {
        OSSL_PARAM params[3];
        size_t params_n = 0;
        int flags = EVP_MD_CTX_test_flags(mctx, ~EVP_MD_CTX_FLAG_NO_INIT);

        /* TODO(3.0) "flags" isn't quite right, i.e. a quick hack for now */
        params[params_n++] =
            OSSL_PARAM_construct_int(OSSL_MAC_PARAM_FLAGS, &flags);
        if (set_key)
            params[params_n++] =
                OSSL_PARAM_construct_octet_string(OSSL_MAC_PARAM_KEY,
                                                  key->data, key->length);
        params[params_n++] = OSSL_PARAM_construct_end();
        rv = EVP_MAC_CTX_set_params(hctx->ctx, params);
    }
    return rv;
}