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
struct TYPE_5__ {int /*<<< orphan*/ * n; int /*<<< orphan*/ * e; } ;
struct TYPE_6__ {TYPE_1__ rsa; } ;
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
 int /*<<< orphan*/ * BN_new () ; 
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_rsa_encrypt(PGP_PubKey *pk, PGP_MPI *_m, PGP_MPI **c_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	BIGNUM	   *m = mpi_to_bn(_m);
	BIGNUM	   *e = mpi_to_bn(pk->pub.rsa.e);
	BIGNUM	   *n = mpi_to_bn(pk->pub.rsa.n);
	BIGNUM	   *c = BN_new();
	BN_CTX	   *tmp = BN_CTX_new();

	if (!m || !e || !n || !c || !tmp)
		goto err;

	/*
	 * c = m ^ e
	 */
	if (!BN_mod_exp(c, m, e, n, tmp))
		goto err;

	*c_p = bn_to_mpi(c);
	if (*c_p)
		res = 0;
err:
	if (tmp)
		BN_CTX_free(tmp);
	if (c)
		BN_clear_free(c);
	if (n)
		BN_clear_free(n);
	if (e)
		BN_clear_free(e);
	if (m)
		BN_clear_free(m);
	return res;
}