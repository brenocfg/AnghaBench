#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  free_func; int /*<<< orphan*/  dup_func; int /*<<< orphan*/  new_func; } ;
struct TYPE_8__ {int /*<<< orphan*/  meth; } ;
struct TYPE_7__ {int /*<<< orphan*/  ex_data_lock; } ;
typedef  TYPE_1__ OSSL_EX_DATA_GLOBAL ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ EX_CALLBACKS ;
typedef  TYPE_3__ EX_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_dup ; 
 int /*<<< orphan*/  dummy_free ; 
 int /*<<< orphan*/  dummy_new ; 
 TYPE_2__* get_and_lock (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* openssl_ctx_get_ex_data_global (int /*<<< orphan*/ *) ; 
 int sk_EX_CALLBACK_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_EX_CALLBACK_value (int /*<<< orphan*/ ,int) ; 

int crypto_free_ex_index_ex(OPENSSL_CTX *ctx, int class_index, int idx)
{
    EX_CALLBACKS *ip = get_and_lock(ctx, class_index);
    EX_CALLBACK *a;
    int toret = 0;
    OSSL_EX_DATA_GLOBAL *global = openssl_ctx_get_ex_data_global(ctx);

    if (global == NULL)
        return 0;

    ip = get_and_lock(ctx, class_index);
    if (ip == NULL)
        return 0;
    if (idx < 0 || idx >= sk_EX_CALLBACK_num(ip->meth))
        goto err;
    a = sk_EX_CALLBACK_value(ip->meth, idx);
    if (a == NULL)
        goto err;
    a->new_func = dummy_new;
    a->dup_func = dummy_dup;
    a->free_func = dummy_free;
    toret = 1;
err:
    CRYPTO_THREAD_unlock(global->ex_data_lock);
    return toret;
}