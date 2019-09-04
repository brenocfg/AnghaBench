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
typedef  int /*<<< orphan*/  CRYPTO_RWLOCK ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

CRYPTO_RWLOCK *CRYPTO_THREAD_lock_new(void)
{
    CRYPTO_RWLOCK *lock;

    if ((lock = OPENSSL_zalloc(sizeof(unsigned int))) == NULL) {
        /* Don't set error, to avoid recursion blowup. */
        return NULL;
    }

    *(unsigned int *)lock = 1;

    return lock;
}