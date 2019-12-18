#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int range; unsigned int iterations; double critical; } ;
typedef  size_t BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (size_t*) ; 
 scalar_t__ BN_get_word (size_t*) ; 
 size_t* BN_new () ; 
 int /*<<< orphan*/  BN_rand_range (size_t*,size_t*) ; 
 int /*<<< orphan*/  BN_set_word (size_t*,unsigned int const) ; 
 int /*<<< orphan*/  OPENSSL_free (size_t*) ; 
 size_t* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_info (char*,double,double const) ; 
 int /*<<< orphan*/  TEST_note (char*,size_t,unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  TEST_ptr (size_t*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_lt (unsigned int,unsigned int const) ; 
 TYPE_1__* rand_range_cases ; 

__attribute__((used)) static int test_rand_range_single(size_t n)
{
    const unsigned int range = rand_range_cases[n].range;
    const unsigned int iterations = rand_range_cases[n].iterations;
    const double critical = rand_range_cases[n].critical;
    const double expected = iterations / (double)range;
    double sum = 0;
    BIGNUM *rng = NULL, *val = NULL;
    size_t *counts;
    unsigned int i, v;
    int res = 0;

    if (!TEST_ptr(counts = OPENSSL_zalloc(sizeof(*counts) * range))
        || !TEST_ptr(rng = BN_new())
        || !TEST_ptr(val = BN_new())
        || !TEST_true(BN_set_word(rng, range)))
        goto err;
    for (i = 0; i < iterations; i++) {
        if (!TEST_true(BN_rand_range(val, rng))
            || !TEST_uint_lt(v = (unsigned int)BN_get_word(val), range))
            goto err;
        counts[v]++;
    }

    for (i = 0; i < range; i++) {
        const double delta = counts[i] - expected;
        sum += delta * delta;
    }
    sum /= expected;

    if (sum > critical) {
        TEST_info("Chi^2 test negative %.4f > %4.f", sum, critical);
        TEST_note("test case %zu  range %u  iterations %u", n + 1, range,
                  iterations);
        goto err;
    }

    res = 1;
err:
    BN_free(rng);
    BN_free(val);
    OPENSSL_free(counts);
    return res;
}