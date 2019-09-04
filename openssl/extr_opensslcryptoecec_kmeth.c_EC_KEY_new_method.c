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
struct TYPE_11__ {scalar_t__ (* init ) (TYPE_1__*) ;} ;
struct TYPE_10__ {int references; int version; TYPE_5__* meth; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  conv_form; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * lock; } ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_EC_KEY ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_KEY_NEW_METHOD ; 
 int /*<<< orphan*/  EC_KEY_free (TYPE_1__*) ; 
 TYPE_5__* EC_KEY_get_default_method () ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ENGINE_get_EC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_default_EC () ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_ENGINE_LIB ; 
 int /*<<< orphan*/  ERR_R_INIT_FAIL ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  POINT_CONVERSION_UNCOMPRESSED ; 
 scalar_t__ stub1 (TYPE_1__*) ; 

EC_KEY *EC_KEY_new_method(ENGINE *engine)
{
    EC_KEY *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        ECerr(EC_F_EC_KEY_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->references = 1;
    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        ECerr(EC_F_EC_KEY_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }

    ret->meth = EC_KEY_get_default_method();
#ifndef OPENSSL_NO_ENGINE
    if (engine != NULL) {
        if (!ENGINE_init(engine)) {
            ECerr(EC_F_EC_KEY_NEW_METHOD, ERR_R_ENGINE_LIB);
            goto err;
        }
        ret->engine = engine;
    } else
        ret->engine = ENGINE_get_default_EC();
    if (ret->engine != NULL) {
        ret->meth = ENGINE_get_EC(ret->engine);
        if (ret->meth == NULL) {
            ECerr(EC_F_EC_KEY_NEW_METHOD, ERR_R_ENGINE_LIB);
            goto err;
        }
    }
#endif

    ret->version = 1;
    ret->conv_form = POINT_CONVERSION_UNCOMPRESSED;

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_EC_KEY, ret, &ret->ex_data)) {
        goto err;
    }

    if (ret->meth->init != NULL && ret->meth->init(ret) == 0) {
        ECerr(EC_F_EC_KEY_NEW_METHOD, ERR_R_INIT_FAIL);
        goto err;
    }
    return ret;

 err:
    EC_KEY_free(ret);
    return NULL;
}