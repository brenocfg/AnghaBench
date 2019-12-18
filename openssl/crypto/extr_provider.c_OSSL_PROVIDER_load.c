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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_provider_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_find (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

OSSL_PROVIDER *OSSL_PROVIDER_load(OPENSSL_CTX *libctx, const char *name)
{
    OSSL_PROVIDER *prov = NULL;

    /* Find it or create it */
    if ((prov = ossl_provider_find(libctx, name, 0)) == NULL
        && (prov = ossl_provider_new(libctx, name, NULL, 0)) == NULL)
        return NULL;

    if (!ossl_provider_activate(prov)) {
        ossl_provider_free(prov);
        return NULL;
    }

    return prov;
}