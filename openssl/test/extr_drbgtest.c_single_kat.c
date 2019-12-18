#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_7__ {int /*<<< orphan*/  kat2len_pr; int /*<<< orphan*/  kat2_pr; int /*<<< orphan*/  adinglen_pr; int /*<<< orphan*/  ading_pr; int /*<<< orphan*/  entropyglen_pr; int /*<<< orphan*/  entropyg_pr; int /*<<< orphan*/  katlen_pr; int /*<<< orphan*/  kat_pr; int /*<<< orphan*/  adinlen_pr; int /*<<< orphan*/  adin_pr; int /*<<< orphan*/  entropyprlen_pr; int /*<<< orphan*/  entropypr_pr; int /*<<< orphan*/  perslen_pr; int /*<<< orphan*/  pers_pr; int /*<<< orphan*/  noncelen_pr; int /*<<< orphan*/  nonce_pr; int /*<<< orphan*/  entropylen_pr; int /*<<< orphan*/  entropy_pr; int /*<<< orphan*/  flags; int /*<<< orphan*/  nid; int /*<<< orphan*/  kat2len; int /*<<< orphan*/  kat2; int /*<<< orphan*/  adin2len; int /*<<< orphan*/  adin2; int /*<<< orphan*/  adinreseedlen; int /*<<< orphan*/  adinreseed; int /*<<< orphan*/  entropyreseedlen; int /*<<< orphan*/  entropyreseed; int /*<<< orphan*/  exlen; int /*<<< orphan*/  expected; int /*<<< orphan*/  adinlen; int /*<<< orphan*/  adin; int /*<<< orphan*/  perslen; int /*<<< orphan*/  pers; int /*<<< orphan*/  noncelen; int /*<<< orphan*/  nonce; int /*<<< orphan*/  entropylen; int /*<<< orphan*/  entropy; } ;
struct TYPE_6__ {int /*<<< orphan*/  entropylen; int /*<<< orphan*/  entropy; scalar_t__ noncecnt; scalar_t__ entropycnt; int /*<<< orphan*/  noncelen; int /*<<< orphan*/  nonce; } ;
typedef  TYPE_1__ TEST_CTX ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  TYPE_2__ DRBG_SELFTEST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_DRBG_free (int /*<<< orphan*/ *) ; 
 int RAND_DRBG_generate (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RAND_DRBG_instantiate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RAND_DRBG_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RAND_DRBG_reseed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RAND_DRBG_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RAND_DRBG_set_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  app_data_index ; 
 int disable_crngt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kat_entropy ; 
 int /*<<< orphan*/  kat_nonce ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uninstantiate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int single_kat(DRBG_SELFTEST_DATA *td)
{
    RAND_DRBG *drbg = NULL;
    TEST_CTX t;
    int failures = 0;
    unsigned char buff[1024];

    /*
     * Test without PR: Instantiate DRBG with test entropy, nonce and
     * personalisation string.
     */
    if (!TEST_ptr(drbg = RAND_DRBG_new(td->nid, td->flags, NULL)))
        return 0;
    if (!TEST_true(RAND_DRBG_set_callbacks(drbg, kat_entropy, NULL,
                                           kat_nonce, NULL))
        || !TEST_true(disable_crngt(drbg))) {
        failures++;
        goto err;
    }
    memset(&t, 0, sizeof(t));
    t.entropy = td->entropy;
    t.entropylen = td->entropylen;
    t.nonce = td->nonce;
    t.noncelen = td->noncelen;
    RAND_DRBG_set_ex_data(drbg, app_data_index, &t);

    if (!TEST_true(RAND_DRBG_instantiate(drbg, td->pers, td->perslen))
            || !TEST_true(RAND_DRBG_generate(drbg, buff, td->exlen, 0,
                                             td->adin, td->adinlen))
            || !TEST_mem_eq(td->expected, td->exlen, buff, td->exlen))
        failures++;

    /* Reseed DRBG with test entropy and additional input */
    t.entropy = td->entropyreseed;
    t.entropylen = td->entropyreseedlen;
    if (!TEST_true(RAND_DRBG_reseed(drbg, td->adinreseed, td->adinreseedlen, 0)
            || !TEST_true(RAND_DRBG_generate(drbg, buff, td->kat2len, 0,
                                             td->adin2, td->adin2len))
            || !TEST_mem_eq(td->kat2, td->kat2len, buff, td->kat2len)))
        failures++;
    uninstantiate(drbg);

    /*
     * Now test with PR: Instantiate DRBG with test entropy, nonce and
     * personalisation string.
     */
    if (!TEST_true(RAND_DRBG_set(drbg, td->nid, td->flags))
            || !TEST_true(RAND_DRBG_set_callbacks(drbg, kat_entropy, NULL,
                                                  kat_nonce, NULL)))
        failures++;
    RAND_DRBG_set_ex_data(drbg, app_data_index, &t);
    t.entropy = td->entropy_pr;
    t.entropylen = td->entropylen_pr;
    t.nonce = td->nonce_pr;
    t.noncelen = td->noncelen_pr;
    t.entropycnt = 0;
    t.noncecnt = 0;
    if (!TEST_true(RAND_DRBG_instantiate(drbg, td->pers_pr, td->perslen_pr)))
        failures++;

    /*
     * Now generate with PR: we need to supply entropy as this will
     * perform a reseed operation.
     */
    t.entropy = td->entropypr_pr;
    t.entropylen = td->entropyprlen_pr;
    if (!TEST_true(RAND_DRBG_generate(drbg, buff, td->katlen_pr, 1,
                                      td->adin_pr, td->adinlen_pr))
            || !TEST_mem_eq(td->kat_pr, td->katlen_pr, buff, td->katlen_pr))
        failures++;

    /*
     * Now generate again with PR: supply new entropy again.
     */
    t.entropy = td->entropyg_pr;
    t.entropylen = td->entropyglen_pr;

    if (!TEST_true(RAND_DRBG_generate(drbg, buff, td->kat2len_pr, 1,
                                      td->ading_pr, td->adinglen_pr))
                || !TEST_mem_eq(td->kat2_pr, td->kat2len_pr,
                                buff, td->kat2len_pr))
        failures++;

err:
    uninstantiate(drbg);
    RAND_DRBG_free(drbg);
    return failures == 0;
}