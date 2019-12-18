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
 int /*<<< orphan*/  OPENSSL_thread_stop () ; 
 int /*<<< orphan*/  run_multi_thread_test () ; 

__attribute__((used)) static void *thread_run(void *arg)
{
    run_multi_thread_test();
    /*
     * Because we're linking with a static library, we must stop each
     * thread explicitly, or so says OPENSSL_thread_stop(3)
     */
    OPENSSL_thread_stop();
    return NULL;
}