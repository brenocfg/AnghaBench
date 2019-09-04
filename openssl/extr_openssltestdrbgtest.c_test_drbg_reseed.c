#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {int reseed_count; } ;
struct TYPE_10__ {int reseed_count; } ;
struct TYPE_9__ {int reseed_count; } ;
struct TYPE_8__ {int reseed_prop_counter; int state; scalar_t__ reseed_time; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 int DRBG_ERROR ; 
 int DRBG_READY ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int RAND_bytes (unsigned char*,int) ; 
 int RAND_priv_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_le (int,int) ; 
 int /*<<< orphan*/  TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_time_t_ge (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TEST_time_t_le (scalar_t__,scalar_t__) ; 
 TYPE_7__ master_ctx ; 
 TYPE_6__ private_ctx ; 
 TYPE_5__ public_ctx ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_drbg_reseed(int expect_success,
                            RAND_DRBG *master,
                            RAND_DRBG *public,
                            RAND_DRBG *private,
                            int expect_master_reseed,
                            int expect_public_reseed,
                            int expect_private_reseed,
                            time_t reseed_time
                           )
{
    unsigned char buf[32];
    time_t before_reseed, after_reseed;
    int expected_state = (expect_success ? DRBG_READY : DRBG_ERROR);

    /*
     * step 1: check preconditions
     */

    /* Test whether seed propagation is enabled */
    if (!TEST_int_ne(master->reseed_prop_counter, 0)
        || !TEST_int_ne(public->reseed_prop_counter, 0)
        || !TEST_int_ne(private->reseed_prop_counter, 0))
        return 0;

    /* Check whether the master DRBG's reseed counter is the largest one */
    if (!TEST_int_le(public->reseed_prop_counter, master->reseed_prop_counter)
        || !TEST_int_le(private->reseed_prop_counter, master->reseed_prop_counter))
        return 0;

    /*
     * step 2: generate random output
     */

    if (reseed_time == 0)
        reseed_time = time(NULL);

    /* Generate random output from the public and private DRBG */
    before_reseed = expect_master_reseed == 1 ? reseed_time : 0;
    if (!TEST_int_eq(RAND_bytes(buf, sizeof(buf)), expect_success)
        || !TEST_int_eq(RAND_priv_bytes(buf, sizeof(buf)), expect_success))
        return 0;
    after_reseed = time(NULL);


    /*
     * step 3: check postconditions
     */

    /* Test whether reseeding succeeded as expected */
    if (!TEST_int_eq(master->state, expected_state)
        || !TEST_int_eq(public->state, expected_state)
        || !TEST_int_eq(private->state, expected_state))
        return 0;

    if (expect_master_reseed >= 0) {
        /* Test whether master DRBG was reseeded as expected */
        if (!TEST_int_eq(master_ctx.reseed_count, expect_master_reseed))
            return 0;
    }

    if (expect_public_reseed >= 0) {
        /* Test whether public DRBG was reseeded as expected */
        if (!TEST_int_eq(public_ctx.reseed_count, expect_public_reseed))
            return 0;
    }

    if (expect_private_reseed >= 0) {
        /* Test whether public DRBG was reseeded as expected */
        if (!TEST_int_eq(private_ctx.reseed_count, expect_private_reseed))
            return 0;
    }

    if (expect_success == 1) {
        /* Test whether all three reseed counters are synchronized */
        if (!TEST_int_eq(public->reseed_prop_counter, master->reseed_prop_counter)
            || !TEST_int_eq(private->reseed_prop_counter, master->reseed_prop_counter))
            return 0;

        /* Test whether reseed time of master DRBG is set correctly */
        if (!TEST_time_t_le(before_reseed, master->reseed_time)
            || !TEST_time_t_le(master->reseed_time, after_reseed))
            return 0;

        /* Test whether reseed times of child DRBGs are synchronized with master */
        if (!TEST_time_t_ge(public->reseed_time, master->reseed_time)
            || !TEST_time_t_ge(private->reseed_time, master->reseed_time))
            return 0;
    } else {
        ERR_clear_error();
    }

    return 1;
}