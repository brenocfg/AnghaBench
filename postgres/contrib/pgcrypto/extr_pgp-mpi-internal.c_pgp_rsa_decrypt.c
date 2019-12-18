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
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_7__ {int /*<<< orphan*/ * n; } ;
struct TYPE_8__ {TYPE_1__ rsa; } ;
struct TYPE_9__ {int /*<<< orphan*/ * d; } ;
struct TYPE_10__ {TYPE_3__ rsa; } ;
struct TYPE_11__ {TYPE_2__ pub; TYPE_4__ sec; } ;
typedef  TYPE_5__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;

/* Variables and functions */
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_new () ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_rsa_decrypt(PGP_PubKey *pk, PGP_MPI *_c, PGP_MPI **m_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	mpz_t	   *c = mpi_to_bn(_c);
	mpz_t	   *d = mpi_to_bn(pk->sec.rsa.d);
	mpz_t	   *n = mpi_to_bn(pk->pub.rsa.n);
	mpz_t	   *m = mp_new();

	if (!m || !d || !n || !c)
		goto err;

	/*
	 * m = c ^ d
	 */
	mp_int_exptmod(c, d, n, m);

	*m_p = bn_to_mpi(m);
	if (*m_p)
		res = 0;
err:
	mp_clear_free(m);
	mp_clear_free(n);
	mp_clear_free(d);
	mp_clear_free(c);
	return res;
}