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
struct provider_store_st {int dummy; } ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_GET_PROVIDER_STORE ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_CTX_PROVIDER_STORE_INDEX ; 
 struct provider_store_st* openssl_ctx_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  provider_store_method ; 

__attribute__((used)) static struct provider_store_st *get_provider_store(OPENSSL_CTX *libctx)
{
    struct provider_store_st *store = NULL;

    store = openssl_ctx_get_data(libctx, OPENSSL_CTX_PROVIDER_STORE_INDEX,
                                 &provider_store_method);
    if (store == NULL)
        CRYPTOerr(CRYPTO_F_GET_PROVIDER_STORE, ERR_R_INTERNAL_ERROR);
    return store;
}