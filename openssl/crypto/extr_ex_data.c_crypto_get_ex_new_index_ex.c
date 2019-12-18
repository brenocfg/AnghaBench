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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {long argl; int /*<<< orphan*/ * free_func; int /*<<< orphan*/ * dup_func; int /*<<< orphan*/ * new_func; void* argp; } ;
struct TYPE_9__ {int /*<<< orphan*/ * meth; } ;
struct TYPE_8__ {int /*<<< orphan*/  ex_data_lock; } ;
typedef  TYPE_1__ OSSL_EX_DATA_GLOBAL ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ EX_CALLBACKS ;
typedef  TYPE_3__ EX_CALLBACK ;
typedef  int /*<<< orphan*/  CRYPTO_EX_new ;
typedef  int /*<<< orphan*/  CRYPTO_EX_free ;
typedef  int /*<<< orphan*/  CRYPTO_EX_dup ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_CRYPTO_GET_EX_NEW_INDEX_EX ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_3__*) ; 
 scalar_t__ OPENSSL_malloc (int) ; 
 TYPE_2__* get_and_lock (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* openssl_ctx_get_ex_data_global (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_EX_CALLBACK_new_null () ; 
 int sk_EX_CALLBACK_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_EX_CALLBACK_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_EX_CALLBACK_set (int /*<<< orphan*/ *,int,TYPE_3__*) ; 

int crypto_get_ex_new_index_ex(OPENSSL_CTX *ctx, int class_index, long argl,
                               void *argp, CRYPTO_EX_new *new_func,
                               CRYPTO_EX_dup *dup_func,
                               CRYPTO_EX_free *free_func)
{
    int toret = -1;
    EX_CALLBACK *a;
    EX_CALLBACKS *ip;
    OSSL_EX_DATA_GLOBAL *global = openssl_ctx_get_ex_data_global(ctx);

    if (global == NULL)
        return -1;

    ip = get_and_lock(ctx, class_index);
    if (ip == NULL)
        return -1;

    if (ip->meth == NULL) {
        ip->meth = sk_EX_CALLBACK_new_null();
        /* We push an initial value on the stack because the SSL
         * "app_data" routines use ex_data index zero.  See RT 3710. */
        if (ip->meth == NULL
            || !sk_EX_CALLBACK_push(ip->meth, NULL)) {
            CRYPTOerr(CRYPTO_F_CRYPTO_GET_EX_NEW_INDEX_EX, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    a = (EX_CALLBACK *)OPENSSL_malloc(sizeof(*a));
    if (a == NULL) {
        CRYPTOerr(CRYPTO_F_CRYPTO_GET_EX_NEW_INDEX_EX, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    a->argl = argl;
    a->argp = argp;
    a->new_func = new_func;
    a->dup_func = dup_func;
    a->free_func = free_func;

    if (!sk_EX_CALLBACK_push(ip->meth, NULL)) {
        CRYPTOerr(CRYPTO_F_CRYPTO_GET_EX_NEW_INDEX_EX, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(a);
        goto err;
    }
    toret = sk_EX_CALLBACK_num(ip->meth) - 1;
    (void)sk_EX_CALLBACK_set(ip->meth, toret, a);

 err:
    CRYPTO_THREAD_unlock(global->ex_data_lock);
    return toret;
}