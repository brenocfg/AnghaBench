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
struct TYPE_6__ {int cache; int references; int /*<<< orphan*/ * get_cert_methods; int /*<<< orphan*/ * objs; int /*<<< orphan*/ * param; int /*<<< orphan*/ * lock; int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ X509_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_X509_STORE ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  X509_F_X509_STORE_NEW ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_VERIFY_PARAM_new () ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_LOOKUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_LOOKUP_new_null () ; 
 int /*<<< orphan*/  sk_X509_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_OBJECT_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509_object_cmp ; 

X509_STORE *X509_STORE_new(void)
{
    X509_STORE *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        X509err(X509_F_X509_STORE_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    if ((ret->objs = sk_X509_OBJECT_new(x509_object_cmp)) == NULL) {
        X509err(X509_F_X509_STORE_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    ret->cache = 1;
    if ((ret->get_cert_methods = sk_X509_LOOKUP_new_null()) == NULL) {
        X509err(X509_F_X509_STORE_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if ((ret->param = X509_VERIFY_PARAM_new()) == NULL) {
        X509err(X509_F_X509_STORE_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_X509_STORE, ret, &ret->ex_data)) {
        X509err(X509_F_X509_STORE_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        X509err(X509_F_X509_STORE_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    ret->references = 1;
    return ret;

err:
    X509_VERIFY_PARAM_free(ret->param);
    sk_X509_OBJECT_free(ret->objs);
    sk_X509_LOOKUP_free(ret->get_cert_methods);
    OPENSSL_free(ret);
    return NULL;
}