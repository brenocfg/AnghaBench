#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  private_drbg; int /*<<< orphan*/  public_drbg; } ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ DRBG_GLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* drbg_get_global (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbg_delete_thread_state(void *arg)
{
    OPENSSL_CTX *ctx = arg;
    DRBG_GLOBAL *dgbl = drbg_get_global(ctx);
    RAND_DRBG *drbg;

    if (dgbl == NULL)
        return;
    drbg = CRYPTO_THREAD_get_local(&dgbl->public_drbg);
    CRYPTO_THREAD_set_local(&dgbl->public_drbg, NULL);
    RAND_DRBG_free(drbg);

    drbg = CRYPTO_THREAD_get_local(&dgbl->private_drbg);
    CRYPTO_THREAD_set_local(&dgbl->private_drbg, NULL);
    RAND_DRBG_free(drbg);
}