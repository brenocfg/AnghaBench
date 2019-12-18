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
struct TYPE_2__ {size_t noncelen; scalar_t__ nonce; int /*<<< orphan*/  noncecnt; } ;
typedef  TYPE_1__ TEST_CTX ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 scalar_t__ RAND_DRBG_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_data_index ; 

__attribute__((used)) static size_t kat_nonce(RAND_DRBG *drbg, unsigned char **pout,
                        int entropy, size_t min_len, size_t max_len)
{
    TEST_CTX *t = (TEST_CTX *)RAND_DRBG_get_ex_data(drbg, app_data_index);

    t->noncecnt++;
    *pout = (unsigned char *)t->nonce;
    return t->noncelen;
}