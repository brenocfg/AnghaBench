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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int MAX_LEN ; 
 scalar_t__ RAND_bytes (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SRP_Calc_x (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  SRP_RANDOM_SALT_LEN ; 

int SRP_create_verifier_BN(const char *user, const char *pass, BIGNUM **salt,
                           BIGNUM **verifier, const BIGNUM *N,
                           const BIGNUM *g)
{
    int result = 0;
    BIGNUM *x = NULL;
    BN_CTX *bn_ctx = BN_CTX_new();
    unsigned char tmp2[MAX_LEN];
    BIGNUM *salttmp = NULL;

    if ((user == NULL) ||
        (pass == NULL) ||
        (salt == NULL) ||
        (verifier == NULL) || (N == NULL) || (g == NULL) || (bn_ctx == NULL))
        goto err;

    if (*salt == NULL) {
        if (RAND_bytes(tmp2, SRP_RANDOM_SALT_LEN) <= 0)
            goto err;

        salttmp = BN_bin2bn(tmp2, SRP_RANDOM_SALT_LEN, NULL);
        if (salttmp == NULL)
            goto err;
    } else {
        salttmp = *salt;
    }

    x = SRP_Calc_x(salttmp, user, pass);
    if (x == NULL)
        goto err;

    *verifier = BN_new();
    if (*verifier == NULL)
        goto err;

    if (!BN_mod_exp(*verifier, g, x, N, bn_ctx)) {
        BN_clear_free(*verifier);
        goto err;
    }

    result = 1;
    *salt = salttmp;

 err:
    if (salt != NULL && *salt != salttmp)
        BN_clear_free(salttmp);
    BN_clear_free(x);
    BN_CTX_free(bn_ctx);
    return result;
}