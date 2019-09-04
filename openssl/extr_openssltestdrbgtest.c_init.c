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
struct TYPE_7__ {int /*<<< orphan*/  noncelen; int /*<<< orphan*/  nonce; int /*<<< orphan*/  entropylen; int /*<<< orphan*/  entropy; int /*<<< orphan*/  flags; int /*<<< orphan*/  nid; } ;
struct TYPE_6__ {scalar_t__ noncecnt; scalar_t__ entropycnt; int /*<<< orphan*/  noncelen; int /*<<< orphan*/  nonce; int /*<<< orphan*/  entropylen; int /*<<< orphan*/  entropy; } ;
typedef  TYPE_1__ TEST_CTX ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  TYPE_2__ DRBG_SELFTEST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_DRBG_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_DRBG_set_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_data_index ; 
 int /*<<< orphan*/  kat_entropy ; 
 int /*<<< orphan*/  kat_nonce ; 

__attribute__((used)) static int init(RAND_DRBG *drbg, DRBG_SELFTEST_DATA *td, TEST_CTX *t)
{
    if (!TEST_true(RAND_DRBG_set(drbg, td->nid, td->flags))
            || !TEST_true(RAND_DRBG_set_callbacks(drbg, kat_entropy, NULL,
                                                  kat_nonce, NULL)))
        return 0;
    RAND_DRBG_set_ex_data(drbg, app_data_index, t);
    t->entropy = td->entropy;
    t->entropylen = td->entropylen;
    t->nonce = td->nonce;
    t->noncelen = td->noncelen;
    t->entropycnt = 0;
    t->noncecnt = 0;
    return 1;
}