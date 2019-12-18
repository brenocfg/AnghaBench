#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * p; int /*<<< orphan*/ * q; int /*<<< orphan*/ * iqmp; int /*<<< orphan*/ * e; int /*<<< orphan*/ * dmq1; int /*<<< orphan*/ * dmp1; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_sub_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_value_one () ; 

int rsa_check_crt_components(const RSA *rsa, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *r = NULL, *p1 = NULL, *q1 = NULL;

    /* check if only some of the crt components are set */
    if (rsa->dmp1 == NULL || rsa->dmq1 == NULL || rsa->iqmp == NULL) {
        if (rsa->dmp1 != NULL || rsa->dmq1 != NULL || rsa->iqmp != NULL)
            return 0;
        return 1; /* return ok if all components are NULL */
    }

    BN_CTX_start(ctx);
    r = BN_CTX_get(ctx);
    p1 = BN_CTX_get(ctx);
    q1 = BN_CTX_get(ctx);
    ret = (q1 != NULL)
          /* p1 = p -1 */
          && (BN_copy(p1, rsa->p) != NULL)
          && BN_sub_word(p1, 1)
          /* q1 = q - 1 */
          && (BN_copy(q1, rsa->q) != NULL)
          && BN_sub_word(q1, 1)
          /* (a) 1 < dP < (p – 1). */
          && (BN_cmp(rsa->dmp1, BN_value_one()) > 0)
          && (BN_cmp(rsa->dmp1, p1) < 0)
          /* (b) 1 < dQ < (q - 1). */
          && (BN_cmp(rsa->dmq1, BN_value_one()) > 0)
          && (BN_cmp(rsa->dmq1, q1) < 0)
          /* (c) 1 < qInv < p */
          && (BN_cmp(rsa->iqmp, BN_value_one()) > 0)
          && (BN_cmp(rsa->iqmp, rsa->p) < 0)
          /* (d) 1 = (dP . e) mod (p - 1)*/
          && BN_mod_mul(r, rsa->dmp1, rsa->e, p1, ctx)
          && BN_is_one(r)
          /* (e) 1 = (dQ . e) mod (q - 1) */
          && BN_mod_mul(r, rsa->dmq1, rsa->e, q1, ctx)
          && BN_is_one(r)
          /* (f) 1 = (qInv . q) mod p */
          && BN_mod_mul(r, rsa->iqmp, rsa->q, rsa->p, ctx)
          && BN_is_one(r);
    BN_clear(p1);
    BN_clear(q1);
    BN_CTX_end(ctx);
    return ret;
}