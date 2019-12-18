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
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_F_EVP_SET_DEFAULT_PROPERTIES ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_evp_method_store (int /*<<< orphan*/ *) ; 
 int ossl_method_store_set_global_properties (int /*<<< orphan*/ *,char const*) ; 

int EVP_set_default_properties(OPENSSL_CTX *libctx, const char *propq)
{
    OSSL_METHOD_STORE *store = get_evp_method_store(libctx);

    if (store != NULL)
        return ossl_method_store_set_global_properties(store, propq);
    EVPerr(EVP_F_EVP_SET_DEFAULT_PROPERTIES, ERR_R_INTERNAL_ERROR);
    return 0;
}