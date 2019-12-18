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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_DRBG_get_ex_new_index (long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_data_index ; 
 int /*<<< orphan*/  drbg_ctr_nelem ; 
 int /*<<< orphan*/  drbg_hash_nelem ; 
 int /*<<< orphan*/  drbg_hmac_nelem ; 
 int /*<<< orphan*/  test_cavs_ctr ; 
 int /*<<< orphan*/  test_cavs_hash ; 
 int /*<<< orphan*/  test_cavs_hmac ; 

int setup_tests(void)
{
    app_data_index = RAND_DRBG_get_ex_new_index(0L, NULL, NULL, NULL, NULL);

    ADD_ALL_TESTS(test_cavs_ctr,  drbg_ctr_nelem);
    ADD_ALL_TESTS(test_cavs_hmac, drbg_hmac_nelem);
    ADD_ALL_TESTS(test_cavs_hash, drbg_hash_nelem);

    return 1;
}