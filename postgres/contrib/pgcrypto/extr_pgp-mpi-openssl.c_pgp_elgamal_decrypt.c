#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * x; } ;
struct TYPE_10__ {TYPE_3__ elg; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
struct TYPE_8__ {TYPE_1__ elg; } ;
struct TYPE_11__ {TYPE_4__ sec; TYPE_2__ pub; } ;
typedef  TYPE_5__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_elgamal_decrypt(PGP_PubKey *pk, PGP_MPI *_c1, PGP_MPI *_c2,
					PGP_MPI **msg_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	BIGNUM	   *c1 = mpi_to_bn(_c1);
	BIGNUM	   *c2 = mpi_to_bn(_c2);
	BIGNUM	   *p = mpi_to_bn(pk->pub.elg.p);
	BIGNUM	   *x = mpi_to_bn(pk->sec.elg.x);
	BIGNUM	   *c1x = BN_new();
	BIGNUM	   *div = BN_new();
	BIGNUM	   *m = BN_new();
	BN_CTX	   *tmp = BN_CTX_new();

	if (!c1 || !c2 || !p || !x || !c1x || !div || !m || !tmp)
		goto err;

	/*
	 * m = c2 / (c1^x)
	 */
	if (!BN_mod_exp(c1x, c1, x, p, tmp))
		goto err;
	if (!BN_mod_inverse(div, c1x, p, tmp))
		goto err;
	if (!BN_mod_mul(m, c2, div, p, tmp))
		goto err;

	/* result */
	*msg_p = bn_to_mpi(m);
	if (*msg_p)
		res = 0;
err:
	if (tmp)
		BN_CTX_free(tmp);
	if (m)
		BN_clear_free(m);
	if (div)
		BN_clear_free(div);
	if (c1x)
		BN_clear_free(c1x);
	if (x)
		BN_clear_free(x);
	if (p)
		BN_clear_free(p);
	if (c2)
		BN_clear_free(c2);
	if (c1)
		BN_clear_free(c1);
	return res;
}