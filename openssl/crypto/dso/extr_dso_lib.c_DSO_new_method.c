#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* init ) (TYPE_1__*) ;} ;
struct TYPE_9__ {int references; TYPE_3__* meth; int /*<<< orphan*/ * meth_data; int /*<<< orphan*/ * lock; } ;
typedef  int /*<<< orphan*/  DSO_METHOD ;
typedef  TYPE_1__ DSO ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  DSO_F_DSO_NEW_METHOD ; 
 TYPE_3__* DSO_METHOD_openssl () ; 
 int /*<<< orphan*/  DSO_free (TYPE_1__*) ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 TYPE_3__* default_DSO_meth ; 
 int /*<<< orphan*/  sk_void_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_void_new_null () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static DSO *DSO_new_method(DSO_METHOD *meth)
{
    DSO *ret;

    if (default_DSO_meth == NULL) {
        /*
         * We default to DSO_METH_openssl() which in turn defaults to
         * stealing the "best available" method. Will fallback to
         * DSO_METH_null() in the worst case.
         */
        default_DSO_meth = DSO_METHOD_openssl();
    }
    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL) {
        DSOerr(DSO_F_DSO_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->meth_data = sk_void_new_null();
    if (ret->meth_data == NULL) {
        /* sk_new doesn't generate any errors so we do */
        DSOerr(DSO_F_DSO_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }
    ret->meth = default_DSO_meth;
    ret->references = 1;
    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        DSOerr(DSO_F_DSO_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        sk_void_free(ret->meth_data);
        OPENSSL_free(ret);
        return NULL;
    }

    if ((ret->meth->init != NULL) && !ret->meth->init(ret)) {
        DSO_free(ret);
        ret = NULL;
    }

    return ret;
}