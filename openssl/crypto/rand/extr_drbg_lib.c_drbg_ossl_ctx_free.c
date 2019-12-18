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
struct TYPE_3__ {int /*<<< orphan*/  public_drbg; int /*<<< orphan*/  private_drbg; int /*<<< orphan*/  master_drbg; } ;
typedef  TYPE_1__ DRBG_GLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_cleanup_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  RAND_DRBG_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drbg_ossl_ctx_free(void *vdgbl)
{
    DRBG_GLOBAL *dgbl = vdgbl;

    if (dgbl == NULL)
        return;

    RAND_DRBG_free(dgbl->master_drbg);
    CRYPTO_THREAD_cleanup_local(&dgbl->private_drbg);
    CRYPTO_THREAD_cleanup_local(&dgbl->public_drbg);

    OPENSSL_free(dgbl);
}