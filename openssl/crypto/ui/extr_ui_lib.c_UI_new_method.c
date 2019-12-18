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
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_6__ {int /*<<< orphan*/  ex_data; int /*<<< orphan*/  const* meth; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ UI ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_UI ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  UI_F_UI_NEW_METHOD ; 
 int /*<<< orphan*/ * UI_get_default_method () ; 
 int /*<<< orphan*/ * UI_null () ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UI *UI_new_method(const UI_METHOD *method)
{
    UI *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        UIerr(UI_F_UI_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        UIerr(UI_F_UI_NEW_METHOD, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }

    if (method == NULL)
        method = UI_get_default_method();
    if (method == NULL)
        method = UI_null();
    ret->meth = method;

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_UI, ret, &ret->ex_data)) {
        OPENSSL_free(ret);
        return NULL;
    }
    return ret;
}