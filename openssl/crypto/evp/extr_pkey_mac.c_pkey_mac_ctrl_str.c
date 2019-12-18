#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  TYPE_2__ MAC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_MAC_CTX_mac (int /*<<< orphan*/ ) ; 
 int EVP_MAC_CTX_set_params (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_MAC_settable_ctx_params (int /*<<< orphan*/  const*) ; 
 TYPE_2__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 char* OSSL_MAC_PARAM_DIGEST ; 
 char* OSSL_MAC_PARAM_SIZE ; 
 int /*<<< orphan*/  OSSL_PARAM_allocate_from_text (TYPE_1__*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__) ; 
 TYPE_1__ OSSL_PARAM_construct_end () ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int pkey_mac_ctrl_str(EVP_PKEY_CTX *ctx,
                              const char *type, const char *value)
{
    MAC_PKEY_CTX *hctx = EVP_PKEY_CTX_get_data(ctx);
    const EVP_MAC *mac = EVP_MAC_CTX_mac(hctx->ctx);
    OSSL_PARAM params[2];
    int ok = 0;

    /*
     * Translation of some control names that are equivalent to a single
     * parameter name.
     *
     * "md" and "digest" are the same thing, we use the single "digest"
     *
     * "digestsize" was a setting control in siphash, but naming wise,
     * it's really the same as "size".
     */
    if (strcmp(type, "md") == 0)
        type = OSSL_MAC_PARAM_DIGEST;
    else if (strcmp(type, "digestsize") == 0)
        type = OSSL_MAC_PARAM_SIZE;

    if (!OSSL_PARAM_allocate_from_text(&params[0],
                                       EVP_MAC_settable_ctx_params(mac),
                                       type, value, strlen(value) + 1))
        return 0;
    params[1] = OSSL_PARAM_construct_end();
    ok = EVP_MAC_CTX_set_params(hctx->ctx, params);
    OPENSSL_free(params[0].data);
    return ok;
}