#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ adinlen; int /*<<< orphan*/  adin; scalar_t__ exlen; scalar_t__ perslen; int /*<<< orphan*/  pers; int /*<<< orphan*/  flags; int /*<<< orphan*/  nid; } ;
struct TYPE_20__ {unsigned int reseed_gen_counter; unsigned int reseed_interval; int /*<<< orphan*/  data; scalar_t__ min_entropylen; scalar_t__ max_entropylen; scalar_t__ max_adinlen; scalar_t__ max_request; scalar_t__ max_noncelen; scalar_t__ min_noncelen; scalar_t__ max_perslen; } ;
struct TYPE_19__ {unsigned int entropycnt; scalar_t__ entropylen; scalar_t__ noncelen; } ;
typedef  TYPE_1__ TEST_CTX ;
typedef  TYPE_2__ RAND_DRBG ;
typedef  TYPE_3__ DRBG_SELFTEST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_DRBG_free (TYPE_2__*) ; 
 int /*<<< orphan*/  RAND_DRBG_generate (TYPE_2__*,unsigned char*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RAND_DRBG_instantiate (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* RAND_DRBG_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RAND_DRBG_reseed (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (unsigned int,unsigned int) ; 
 scalar_t__ TEST_int_le (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_crngt (TYPE_2__*) ; 
 int /*<<< orphan*/  init (TYPE_2__*,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  instantiate (TYPE_2__*,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uninstantiate (TYPE_2__*) ; 

__attribute__((used)) static int error_check(DRBG_SELFTEST_DATA *td)
{
    static char zero[sizeof(RAND_DRBG)];
    RAND_DRBG *drbg = NULL;
    TEST_CTX t;
    unsigned char buff[1024];
    unsigned int reseed_counter_tmp;
    int ret = 0;

    if (!TEST_ptr(drbg = RAND_DRBG_new(td->nid, td->flags, NULL))
        || !TEST_true(disable_crngt(drbg)))
        goto err;

    /*
     * Personalisation string tests
     */

    /* Test detection of too large personalisation string */
    if (!init(drbg, td, &t)
            || RAND_DRBG_instantiate(drbg, td->pers, drbg->max_perslen + 1) > 0)
        goto err;

    /*
     * Entropy source tests
     */

    /* Test entropy source failure detection: i.e. returns no data */
    t.entropylen = 0;
    if (TEST_int_le(RAND_DRBG_instantiate(drbg, td->pers, td->perslen), 0))
        goto err;

    /* Try to generate output from uninstantiated DRBG */
    if (!TEST_false(RAND_DRBG_generate(drbg, buff, td->exlen, 0,
                                       td->adin, td->adinlen))
            || !uninstantiate(drbg))
        goto err;

    /* Test insufficient entropy */
    t.entropylen = drbg->min_entropylen - 1;
    if (!init(drbg, td, &t)
            || RAND_DRBG_instantiate(drbg, td->pers, td->perslen) > 0
            || !uninstantiate(drbg))
        goto err;

    /* Test too much entropy */
    t.entropylen = drbg->max_entropylen + 1;
    if (!init(drbg, td, &t)
            || RAND_DRBG_instantiate(drbg, td->pers, td->perslen) > 0
            || !uninstantiate(drbg))
        goto err;

    /*
     * Nonce tests
     */

    /* Test too small nonce */
    if (drbg->min_noncelen) {
        t.noncelen = drbg->min_noncelen - 1;
        if (!init(drbg, td, &t)
                || RAND_DRBG_instantiate(drbg, td->pers, td->perslen) > 0
                || !uninstantiate(drbg))
            goto err;
    }

    /* Test too large nonce */
    if (drbg->max_noncelen) {
        t.noncelen = drbg->max_noncelen + 1;
        if (!init(drbg, td, &t)
                || RAND_DRBG_instantiate(drbg, td->pers, td->perslen) > 0
                || !uninstantiate(drbg))
            goto err;
    }

    /* Instantiate with valid data, Check generation is now OK */
    if (!instantiate(drbg, td, &t)
            || !TEST_true(RAND_DRBG_generate(drbg, buff, td->exlen, 0,
                                             td->adin, td->adinlen)))
        goto err;

    /* Request too much data for one request */
    if (!TEST_false(RAND_DRBG_generate(drbg, buff, drbg->max_request + 1, 0,
                                       td->adin, td->adinlen)))
        goto err;

    /* Try too large additional input */
    if (!TEST_false(RAND_DRBG_generate(drbg, buff, td->exlen, 0,
                                       td->adin, drbg->max_adinlen + 1)))
        goto err;

    /*
     * Check prediction resistance request fails if entropy source
     * failure.
     */
    t.entropylen = 0;
    if (TEST_false(RAND_DRBG_generate(drbg, buff, td->exlen, 1,
                                      td->adin, td->adinlen))
            || !uninstantiate(drbg))
        goto err;

    /* Instantiate again with valid data */
    if (!instantiate(drbg, td, &t))
        goto err;
    reseed_counter_tmp = drbg->reseed_gen_counter;
    drbg->reseed_gen_counter = drbg->reseed_interval;

    /* Generate output and check entropy has been requested for reseed */
    t.entropycnt = 0;
    if (!TEST_true(RAND_DRBG_generate(drbg, buff, td->exlen, 0,
                                      td->adin, td->adinlen))
            || !TEST_int_eq(t.entropycnt, 1)
            || !TEST_int_eq(drbg->reseed_gen_counter, reseed_counter_tmp + 1)
            || !uninstantiate(drbg))
        goto err;

    /*
     * Check prediction resistance request fails if entropy source
     * failure.
     */
    t.entropylen = 0;
    if (!TEST_false(RAND_DRBG_generate(drbg, buff, td->exlen, 1,
                                       td->adin, td->adinlen))
            || !uninstantiate(drbg))
        goto err;

    /* Test reseed counter works */
    if (!instantiate(drbg, td, &t))
        goto err;
    reseed_counter_tmp = drbg->reseed_gen_counter;
    drbg->reseed_gen_counter = drbg->reseed_interval;

    /* Generate output and check entropy has been requested for reseed */
    t.entropycnt = 0;
    if (!TEST_true(RAND_DRBG_generate(drbg, buff, td->exlen, 0,
                                      td->adin, td->adinlen))
            || !TEST_int_eq(t.entropycnt, 1)
            || !TEST_int_eq(drbg->reseed_gen_counter, reseed_counter_tmp + 1)
            || !uninstantiate(drbg))
        goto err;

    /*
     * Explicit reseed tests
     */

    /* Test explicit reseed with too large additional input */
    if (!instantiate(drbg, td, &t)
            || RAND_DRBG_reseed(drbg, td->adin, drbg->max_adinlen + 1, 0) > 0)
        goto err;

    /* Test explicit reseed with entropy source failure */
    t.entropylen = 0;
    if (!TEST_int_le(RAND_DRBG_reseed(drbg, td->adin, td->adinlen, 0), 0)
            || !uninstantiate(drbg))
        goto err;

    /* Test explicit reseed with too much entropy */
    if (!instantiate(drbg, td, &t))
        goto err;
    t.entropylen = drbg->max_entropylen + 1;
    if (!TEST_int_le(RAND_DRBG_reseed(drbg, td->adin, td->adinlen, 0), 0)
            || !uninstantiate(drbg))
        goto err;

    /* Test explicit reseed with too little entropy */
    if (!instantiate(drbg, td, &t))
        goto err;
    t.entropylen = drbg->min_entropylen - 1;
    if (!TEST_int_le(RAND_DRBG_reseed(drbg, td->adin, td->adinlen, 0), 0)
            || !uninstantiate(drbg))
        goto err;

    /* Standard says we have to check uninstantiate really zeroes */
    if (!TEST_mem_eq(zero, sizeof(drbg->data), &drbg->data, sizeof(drbg->data)))
        goto err;

    ret = 1;

err:
    uninstantiate(drbg);
    RAND_DRBG_free(drbg);
    return ret;
}