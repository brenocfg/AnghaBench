#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_10__ {int reseed_prop_counter; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_DRBG_free (TYPE_1__*) ; 
 int /*<<< orphan*/  RAND_DRBG_generate (TYPE_1__*,unsigned char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_DRBG_instantiate (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* RAND_DRBG_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RAND_DRBG_reseed (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_gt (int,int) ; 
 int /*<<< orphan*/  TEST_mem_ne (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_crngt (TYPE_1__*) ; 

__attribute__((used)) static int test_rand_drbg_prediction_resistance(void)
{
    RAND_DRBG *m = NULL, *i = NULL, *s = NULL;
    unsigned char buf1[51], buf2[sizeof(buf1)];
    int ret = 0, mreseed, ireseed, sreseed;

    /* Initialise a three long DRBG chain */
    if (!TEST_ptr(m = RAND_DRBG_new(0, 0, NULL))
        || !TEST_true(disable_crngt(m))
        || !TEST_true(RAND_DRBG_instantiate(m, NULL, 0))
        || !TEST_ptr(i = RAND_DRBG_new(0, 0, m))
        || !TEST_true(RAND_DRBG_instantiate(i, NULL, 0))
        || !TEST_ptr(s = RAND_DRBG_new(0, 0, i))
        || !TEST_true(RAND_DRBG_instantiate(s, NULL, 0)))
        goto err;

    /* During a normal reseed, only the slave DRBG should be reseed */
    mreseed = ++m->reseed_prop_counter;
    ireseed = ++i->reseed_prop_counter;
    sreseed = s->reseed_prop_counter;
    if (!TEST_true(RAND_DRBG_reseed(s, NULL, 0, 0))
        || !TEST_int_eq(m->reseed_prop_counter, mreseed)
        || !TEST_int_eq(i->reseed_prop_counter, ireseed)
        || !TEST_int_gt(s->reseed_prop_counter, sreseed))
        goto err;

    /*
     * When prediction resistance is requested, the request should be
     * propagated to the master, so that the entire DRBG chain reseeds.
     */
    sreseed = s->reseed_prop_counter;
    if (!TEST_true(RAND_DRBG_reseed(s, NULL, 0, 1))
        || !TEST_int_gt(m->reseed_prop_counter, mreseed)
        || !TEST_int_gt(i->reseed_prop_counter, ireseed)
        || !TEST_int_gt(s->reseed_prop_counter, sreseed))
        goto err;

    /* During a normal generate, only the slave DRBG should be reseed */
    mreseed = ++m->reseed_prop_counter;
    ireseed = ++i->reseed_prop_counter;
    sreseed = s->reseed_prop_counter;
    if (!TEST_true(RAND_DRBG_generate(s, buf1, sizeof(buf1), 0, NULL, 0))
        || !TEST_int_eq(m->reseed_prop_counter, mreseed)
        || !TEST_int_eq(i->reseed_prop_counter, ireseed)
        || !TEST_int_gt(s->reseed_prop_counter, sreseed))
        goto err;

    /*
     * When a prediction resistant generate is requested, the request
     * should be propagated to the master, reseeding the entire DRBG chain.
     */
    sreseed = s->reseed_prop_counter;
    if (!TEST_true(RAND_DRBG_generate(s, buf2, sizeof(buf2), 1, NULL, 0))
        || !TEST_int_gt(m->reseed_prop_counter, mreseed)
        || !TEST_int_gt(i->reseed_prop_counter, ireseed)
        || !TEST_int_gt(s->reseed_prop_counter, sreseed)
        || !TEST_mem_ne(buf1, sizeof(buf1), buf2, sizeof(buf2)))
        goto err;

    /* Verify that a normal reseed still only reseeds the slave DRBG */
    mreseed = ++m->reseed_prop_counter;
    ireseed = ++i->reseed_prop_counter;
    sreseed = s->reseed_prop_counter;
    if (!TEST_true(RAND_DRBG_reseed(s, NULL, 0, 0))
        || !TEST_int_eq(m->reseed_prop_counter, mreseed)
        || !TEST_int_eq(i->reseed_prop_counter, ireseed)
        || !TEST_int_gt(s->reseed_prop_counter, sreseed))
        goto err;

    ret = 1;
err:
    RAND_DRBG_free(s);
    RAND_DRBG_free(i);
    RAND_DRBG_free(m);
    return ret;
}