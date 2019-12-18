#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * y; int /*<<< orphan*/ * g; int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {TYPE_1__ elg; } ;
struct TYPE_7__ {TYPE_2__ pub; } ;
typedef  TYPE_3__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int decide_k_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_elgamal_encrypt(PGP_PubKey *pk, PGP_MPI *_m,
					PGP_MPI **c1_p, PGP_MPI **c2_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	int			k_bits;
	BIGNUM	   *m = mpi_to_bn(_m);
	BIGNUM	   *p = mpi_to_bn(pk->pub.elg.p);
	BIGNUM	   *g = mpi_to_bn(pk->pub.elg.g);
	BIGNUM	   *y = mpi_to_bn(pk->pub.elg.y);
	BIGNUM	   *k = BN_new();
	BIGNUM	   *yk = BN_new();
	BIGNUM	   *c1 = BN_new();
	BIGNUM	   *c2 = BN_new();
	BN_CTX	   *tmp = BN_CTX_new();

	if (!m || !p || !g || !y || !k || !yk || !c1 || !c2 || !tmp)
		goto err;

	/*
	 * generate k
	 */
	k_bits = decide_k_bits(BN_num_bits(p));
	if (!BN_rand(k, k_bits, 0, 0))
		goto err;

	/*
	 * c1 = g^k c2 = m * y^k
	 */
	if (!BN_mod_exp(c1, g, k, p, tmp))
		goto err;
	if (!BN_mod_exp(yk, y, k, p, tmp))
		goto err;
	if (!BN_mod_mul(c2, m, yk, p, tmp))
		goto err;

	/* result */
	*c1_p = bn_to_mpi(c1);
	*c2_p = bn_to_mpi(c2);
	if (*c1_p && *c2_p)
		res = 0;
err:
	if (tmp)
		BN_CTX_free(tmp);
	if (c2)
		BN_clear_free(c2);
	if (c1)
		BN_clear_free(c1);
	if (yk)
		BN_clear_free(yk);
	if (k)
		BN_clear_free(k);
	if (y)
		BN_clear_free(y);
	if (g)
		BN_clear_free(g);
	if (p)
		BN_clear_free(p);
	if (m)
		BN_clear_free(m);
	return res;
}