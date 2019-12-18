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
typedef  int time_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/ * RAND_DRBG_get0_private () ; 
 int /*<<< orphan*/ * RAND_DRBG_get0_public () ; 
 int /*<<< orphan*/  RAND_DRBG_set_reseed_time_interval (int /*<<< orphan*/ *,int) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 scalar_t__ RAND_priv_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ multi_thread_rand_bytes_succeeded ; 
 scalar_t__ multi_thread_rand_priv_bytes_succeeded ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void run_multi_thread_test(void)
{
    unsigned char buf[256];
    time_t start = time(NULL);
    RAND_DRBG *public = NULL, *private = NULL;

    if (!TEST_ptr(public = RAND_DRBG_get0_public())
            || !TEST_ptr(private = RAND_DRBG_get0_private())) {
        multi_thread_rand_bytes_succeeded = 0;
        return;
    }
    RAND_DRBG_set_reseed_time_interval(private, 1);
    RAND_DRBG_set_reseed_time_interval(public, 1);

    do {
        if (RAND_bytes(buf, sizeof(buf)) <= 0)
            multi_thread_rand_bytes_succeeded = 0;
        if (RAND_priv_bytes(buf, sizeof(buf)) <= 0)
            multi_thread_rand_priv_bytes_succeeded = 0;
    }
    while(time(NULL) - start < 5);
}