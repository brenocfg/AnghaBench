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
struct drbg_kat {int flags; int type; } ;

/* Variables and functions */
#define  NO_RESEED 130 
#define  PR_FALSE 129 
#define  PR_TRUE 128 
 int TEST_skip (char*) ; 
 int USE_DF ; 
 int /*<<< orphan*/  single_kat_no_reseed (struct drbg_kat const*) ; 
 int /*<<< orphan*/  single_kat_pr_false (struct drbg_kat const*) ; 
 int /*<<< orphan*/  single_kat_pr_true (struct drbg_kat const*) ; 

__attribute__((used)) static int test_cavs_kats(const struct drbg_kat *test[], int i)
{
    const struct drbg_kat *td = test[i];
    int rv = 0;

#ifdef FIPS_MODE
    /* FIPS mode doesn't support instantiating without a derivation function */
    if ((td->flags & USE_DF) == 0)
        return TEST_skip("instantiating without derivation function "
                         "is not supported in FIPS mode");
#endif
    switch (td->type) {
    case NO_RESEED:
        if (!single_kat_no_reseed(td))
            goto err;
        break;
    case PR_FALSE:
        if (!single_kat_pr_false(td))
            goto err;
        break;
    case PR_TRUE:
        if (!single_kat_pr_true(td))
            goto err;
        break;
    default:    /* cant happen */
        goto err;
    }
    rv = 1;
err:
    return rv;
}