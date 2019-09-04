#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  private_drbg ; 
 int /*<<< orphan*/  public_drbg ; 

void drbg_delete_thread_state(void)
{
    RAND_DRBG *drbg;

    drbg = CRYPTO_THREAD_get_local(&public_drbg);
    CRYPTO_THREAD_set_local(&public_drbg, NULL);
    RAND_DRBG_free(drbg);

    drbg = CRYPTO_THREAD_get_local(&private_drbg);
    CRYPTO_THREAD_set_local(&private_drbg, NULL);
    RAND_DRBG_free(drbg);
}