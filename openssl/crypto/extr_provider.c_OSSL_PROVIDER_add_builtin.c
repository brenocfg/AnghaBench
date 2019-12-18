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
typedef  int /*<<< orphan*/  OSSL_provider_init_fn ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OSSL_PROVIDER_ADD_BUILTIN ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int OSSL_PROVIDER_add_builtin(OPENSSL_CTX *libctx, const char *name,
                              OSSL_provider_init_fn *init_fn)
{
    OSSL_PROVIDER *prov = NULL;

    if (name == NULL || init_fn == NULL) {
        CRYPTOerr(CRYPTO_F_OSSL_PROVIDER_ADD_BUILTIN,
                  ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    /* Create it */
    if ((prov = ossl_provider_new(libctx, name, init_fn, 0)) == NULL)
        return 0;

    /*
     * It's safely stored in the internal store at this point,
     * free the returned extra reference
     */
    ossl_provider_free(prov);

    return 1;
}