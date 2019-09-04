#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* init ) (TYPE_1__*) ;int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int references; TYPE_5__* meth; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  flags; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * lock; } ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  TYPE_1__ DH ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_DH ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_F_DH_NEW_METHOD ; 
 int /*<<< orphan*/  DH_free (TYPE_1__*) ; 
 TYPE_5__* DH_get_default_method () ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ENGINE_get_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_default_DH () ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_ENGINE_LIB ; 
 int /*<<< orphan*/  ERR_R_INIT_FAIL ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

DH *DH_new_method(ENGINE *engine)
{
    DH *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        DHerr(DH_F_DH_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->references = 1;
    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        DHerr(DH_F_DH_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }

    ret->meth = DH_get_default_method();
#ifndef OPENSSL_NO_ENGINE
    ret->flags = ret->meth->flags;  /* early default init */
    if (engine) {
        if (!ENGINE_init(engine)) {
            DHerr(DH_F_DH_NEW_METHOD, ERR_R_ENGINE_LIB);
            goto err;
        }
        ret->engine = engine;
    } else
        ret->engine = ENGINE_get_default_DH();
    if (ret->engine) {
        ret->meth = ENGINE_get_DH(ret->engine);
        if (ret->meth == NULL) {
            DHerr(DH_F_DH_NEW_METHOD, ERR_R_ENGINE_LIB);
            goto err;
        }
    }
#endif

    ret->flags = ret->meth->flags;

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_DH, ret, &ret->ex_data))
        goto err;

    if ((ret->meth->init != NULL) && !ret->meth->init(ret)) {
        DHerr(DH_F_DH_NEW_METHOD, ERR_R_INIT_FAIL);
        goto err;
    }

    return ret;

 err:
    DH_free(ret);
    return NULL;
}