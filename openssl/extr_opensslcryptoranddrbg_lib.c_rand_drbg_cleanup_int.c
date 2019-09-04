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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_cleanup_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * master_drbg ; 
 int /*<<< orphan*/  private_drbg ; 
 int /*<<< orphan*/  public_drbg ; 

void rand_drbg_cleanup_int(void)
{
    if (master_drbg != NULL) {
        RAND_DRBG_free(master_drbg);
        master_drbg = NULL;

        CRYPTO_THREAD_cleanup_local(&private_drbg);
        CRYPTO_THREAD_cleanup_local(&public_drbg);
    }
}