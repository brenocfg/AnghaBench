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
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int THREADS ; 
 int /*<<< orphan*/  multi_thread_rand_bytes_succeeded ; 
 int /*<<< orphan*/  multi_thread_rand_priv_bytes_succeeded ; 
 int /*<<< orphan*/  run_multi_thread_test () ; 
 int /*<<< orphan*/  run_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_multi_thread(void)
{
    thread_t t[THREADS];
    int i;

    for (i = 0; i < THREADS; i++)
        run_thread(&t[i]);
    run_multi_thread_test();
    for (i = 0; i < THREADS; i++)
        wait_for_thread(t[i]);

    if (!TEST_true(multi_thread_rand_bytes_succeeded))
        return 0;
    if (!TEST_true(multi_thread_rand_priv_bytes_succeeded))
        return 0;

    return 1;
}