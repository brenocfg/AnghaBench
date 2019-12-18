#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct s_drgb_types {int /*<<< orphan*/  flags; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  buff ;
struct TYPE_14__ {int min_entropylen; } ;
typedef  TYPE_1__ RAND_DRBG ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int CRNGT_BUFSIZ ; 
 int /*<<< orphan*/  OPENSSL_CTX_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_CTX_new () ; 
 int /*<<< orphan*/  RAND_DRBG_free (TYPE_1__*) ; 
 int /*<<< orphan*/  RAND_DRBG_generate (TYPE_1__*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_DRBG_instantiate (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* RAND_DRBG_new_ex (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_reseed (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_DRBG_set_callbacks (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_note (char*,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 size_t crngt_case ; 
 int /*<<< orphan*/  crngt_entropy_cb ; 
 int /*<<< orphan*/ * crngt_get_entropy ; 
 scalar_t__ crngt_idx ; 
 int crngt_num_cases ; 
 struct s_drgb_types* drgb_types ; 
 int /*<<< orphan*/  rand_crngt_cleanup_entropy ; 
 int /*<<< orphan*/  rand_crngt_get_entropy ; 
 int /*<<< orphan*/  rand_crngt_get_entropy_cb ; 
 int /*<<< orphan*/  rand_drbg_cleanup_nonce ; 
 int /*<<< orphan*/  rand_drbg_get_nonce ; 
 int /*<<< orphan*/  uninstantiate (TYPE_1__*) ; 

__attribute__((used)) static int test_crngt(int n)
{
    const struct s_drgb_types *dt = drgb_types + n / crngt_num_cases;
    RAND_DRBG *drbg = NULL;
    unsigned char buff[100];
    size_t ent;
    int res = 0;
    int expect;
    OPENSSL_CTX *ctx = OPENSSL_CTX_new();

    if (!TEST_ptr(ctx))
        return 0;
    if (!TEST_ptr(drbg = RAND_DRBG_new_ex(ctx, dt->nid, dt->flags, NULL)))
        goto err;
    ent = (drbg->min_entropylen + CRNGT_BUFSIZ - 1) / CRNGT_BUFSIZ;
    crngt_case = n % crngt_num_cases;
    crngt_idx = 0;
    crngt_get_entropy = &crngt_entropy_cb;
#ifndef FIPS_MODE
    if (!TEST_true(RAND_DRBG_set_callbacks(drbg, &rand_crngt_get_entropy,
                                           &rand_crngt_cleanup_entropy,
                                           &rand_drbg_get_nonce,
                                           &rand_drbg_cleanup_nonce)))
        goto err;
#endif
    expect = crngt_case == 0 || crngt_case > ent;
    if (!TEST_int_eq(RAND_DRBG_instantiate(drbg, NULL, 0), expect))
        goto err;
    if (!expect)
        goto fin;
    if (!TEST_true(RAND_DRBG_generate(drbg, buff, sizeof(buff), 0, NULL, 0)))
        goto err;

    expect = crngt_case == 0 || crngt_case > 2 * ent;
    if (!TEST_int_eq(RAND_DRBG_reseed(drbg, NULL, 0, 0), expect))
        goto err;
    if (!expect)
        goto fin;
    if (!TEST_true(RAND_DRBG_generate(drbg, buff, sizeof(buff), 0, NULL, 0)))
        goto err;

fin:
    res = 1;
err:
    if (!res)
        TEST_note("DRBG %zd case %zd block %zd", n / crngt_num_cases,
                  crngt_case, crngt_idx);
    uninstantiate(drbg);
    RAND_DRBG_free(drbg);
    crngt_get_entropy = &rand_crngt_get_entropy_cb;
    OPENSSL_CTX_free(ctx);
    return res;
}