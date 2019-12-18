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
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_5__ {int /*<<< orphan*/ * n; int /*<<< orphan*/ * e; } ;
struct TYPE_6__ {TYPE_1__ rsa; } ;
struct TYPE_7__ {TYPE_2__ pub; } ;
typedef  TYPE_3__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;

/* Variables and functions */
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_new () ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_rsa_encrypt(PGP_PubKey *pk, PGP_MPI *_m, PGP_MPI **c_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	mpz_t	   *m = mpi_to_bn(_m);
	mpz_t	   *e = mpi_to_bn(pk->pub.rsa.e);
	mpz_t	   *n = mpi_to_bn(pk->pub.rsa.n);
	mpz_t	   *c = mp_new();

	if (!m || !e || !n || !c)
		goto err;

	/*
	 * c = m ^ e
	 */
	mp_int_exptmod(m, e, n, c);

	*c_p = bn_to_mpi(c);
	if (*c_p)
		res = 0;
err:
	mp_clear_free(c);
	mp_clear_free(n);
	mp_clear_free(e);
	mp_clear_free(m);
	return res;
}