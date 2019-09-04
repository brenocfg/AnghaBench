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
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_lock(void)
{
    CRYPTO_RWLOCK *lock = CRYPTO_THREAD_lock_new();

    if (!TEST_true(CRYPTO_THREAD_read_lock(lock))
        || !TEST_true(CRYPTO_THREAD_unlock(lock)))
        return 0;

    CRYPTO_THREAD_lock_free(lock);

    return 1;
}