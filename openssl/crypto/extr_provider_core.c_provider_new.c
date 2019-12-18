#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * init_function; int /*<<< orphan*/ * name; int /*<<< orphan*/ * refcnt_lock; } ;
typedef  int /*<<< orphan*/  OSSL_provider_init_fn ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_PROVIDER_NEW ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  ossl_provider_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_provider_up_ref (TYPE_1__*) ; 

__attribute__((used)) static OSSL_PROVIDER *provider_new(const char *name,
                                   OSSL_provider_init_fn *init_function)
{
    OSSL_PROVIDER *prov = NULL;

    if ((prov = OPENSSL_zalloc(sizeof(*prov))) == NULL
#ifndef HAVE_ATOMICS
        || (prov->refcnt_lock = CRYPTO_THREAD_lock_new()) == NULL
#endif
        || !ossl_provider_up_ref(prov) /* +1 One reference to be returned */
        || (prov->name = OPENSSL_strdup(name)) == NULL) {
        ossl_provider_free(prov);
        CRYPTOerr(CRYPTO_F_PROVIDER_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    prov->init_function = init_function;
    return prov;
}