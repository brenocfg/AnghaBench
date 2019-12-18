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
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_cleanup_local (int /*<<< orphan*/ *) ; 
 void* CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_init_local (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr_null (void*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destructor_run_count ; 
 int /*<<< orphan*/  run_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_local_destructor ; 
 int /*<<< orphan*/  thread_local_key ; 
 int /*<<< orphan*/  thread_local_thread_cb ; 
 int /*<<< orphan*/  thread_local_thread_cb_ok ; 
 int /*<<< orphan*/  wait_for_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_thread_local(void)
{
    thread_t thread;
    void *ptr = NULL;

    if (!TEST_true(CRYPTO_THREAD_init_local(&thread_local_key,
                                            thread_local_destructor)))
        return 0;

    ptr = CRYPTO_THREAD_get_local(&thread_local_key);
    if (!TEST_ptr_null(ptr)
        || !TEST_true(run_thread(&thread, thread_local_thread_cb))
        || !TEST_true(wait_for_thread(thread))
        || !TEST_int_eq(thread_local_thread_cb_ok, 1))
        return 0;

#if defined(OPENSSL_THREADS) && !defined(CRYPTO_TDEBUG)

    ptr = CRYPTO_THREAD_get_local(&thread_local_key);
    if (!TEST_ptr_null(ptr))
        return 0;

# if !defined(OPENSSL_SYS_WINDOWS)
    if (!TEST_int_eq(destructor_run_count, 1))
        return 0;
# endif
#endif

    if (!TEST_true(CRYPTO_THREAD_cleanup_local(&thread_local_key)))
        return 0;
    return 1;
}