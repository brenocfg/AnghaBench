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
 int /*<<< orphan*/  CRYPTO_THREAD_run_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  once_do_run ; 
 int /*<<< orphan*/  once_run ; 
 int /*<<< orphan*/  once_run_count ; 
 int /*<<< orphan*/  once_run_thread_cb ; 
 int /*<<< orphan*/  run_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_once(void)
{
    thread_t thread;

    if (!TEST_true(run_thread(&thread, once_run_thread_cb))
        || !TEST_true(wait_for_thread(thread))
        || !CRYPTO_THREAD_run_once(&once_run, once_do_run)
        || !TEST_int_eq(once_run_count, 1))
        return 0;
    return 1;
}