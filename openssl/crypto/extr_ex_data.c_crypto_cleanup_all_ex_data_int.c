#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * meth; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ex_data_lock; TYPE_2__* ex_data; } ;
typedef  TYPE_1__ OSSL_EX_DATA_GLOBAL ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ EX_CALLBACKS ;

/* Variables and functions */
 int CRYPTO_EX_INDEX__COUNT ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_cb ; 
 TYPE_1__* openssl_ctx_get_ex_data_global (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_EX_CALLBACK_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void crypto_cleanup_all_ex_data_int(OPENSSL_CTX *ctx)
{
    int i;
    OSSL_EX_DATA_GLOBAL *global = openssl_ctx_get_ex_data_global(ctx);

    if (global == NULL)
        return;

    for (i = 0; i < CRYPTO_EX_INDEX__COUNT; ++i) {
        EX_CALLBACKS *ip = &global->ex_data[i];

        sk_EX_CALLBACK_pop_free(ip->meth, cleanup_cb);
        ip->meth = NULL;
    }

    CRYPTO_THREAD_lock_free(global->ex_data_lock);
    global->ex_data_lock = NULL;
}