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
struct TYPE_9__ {int /*<<< orphan*/ * x; } ;
struct TYPE_10__ {TYPE_3__ elg; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
struct TYPE_8__ {TYPE_1__ elg; } ;
struct TYPE_11__ {TYPE_4__ sec; TYPE_2__ pub; } ;
typedef  TYPE_5__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;

/* Variables and functions */
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_invmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_modmul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_new () ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_elgamal_decrypt(PGP_PubKey *pk, PGP_MPI *_c1, PGP_MPI *_c2,
					PGP_MPI **msg_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	mpz_t	   *c1 = mpi_to_bn(_c1);
	mpz_t	   *c2 = mpi_to_bn(_c2);
	mpz_t	   *p = mpi_to_bn(pk->pub.elg.p);
	mpz_t	   *x = mpi_to_bn(pk->sec.elg.x);
	mpz_t	   *c1x = mp_new();
	mpz_t	   *div = mp_new();
	mpz_t	   *m = mp_new();

	if (!c1 || !c2 || !p || !x || !c1x || !div || !m)
		goto err;

	/*
	 * m = c2 / (c1^x)
	 */
	mp_int_exptmod(c1, x, p, c1x);
	mp_int_invmod(c1x, p, div);
	mp_modmul(c2, div, p, m);

	/* result */
	*msg_p = bn_to_mpi(m);
	if (*msg_p)
		res = 0;
err:
	mp_clear_free(m);
	mp_clear_free(div);
	mp_clear_free(c1x);
	mp_clear_free(x);
	mp_clear_free(p);
	mp_clear_free(c2);
	mp_clear_free(c1);
	return res;
}