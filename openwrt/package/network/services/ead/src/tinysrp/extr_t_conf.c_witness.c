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
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int witness(BIGNUM *w, const BIGNUM *a, const BIGNUM *a1,
	const BIGNUM *a1_odd, int k, BN_CTX *ctx, BN_MONT_CTX *mont)
	{
	if (!BN_mod_exp_mont(w, w, a1_odd, a, ctx, mont)) /* w := w^a1_odd mod a */
		return -1;
	if (BN_is_one(w))
		return 0; /* probably prime */
	if (BN_cmp(w, a1) == 0)
		return 0; /* w == -1 (mod a),  'a' is probably prime */
	while (--k)
		{
		if (!BN_mod_mul(w, w, w, a, ctx)) /* w := w^2 mod a */
			return -1;
		if (BN_is_one(w))
			return 1; /* 'a' is composite, otherwise a previous 'w' would
				   * have been == -1 (mod 'a') */
		if (BN_cmp(w, a1) == 0)
			return 0; /* w == -1 (mod a), 'a' is probably prime */
		}
	/* If we get here, 'w' is the (a-1)/2-th power of the original 'w',
	 * and it is neither -1 nor +1 -- so 'a' cannot be prime */
	return 1;
	}