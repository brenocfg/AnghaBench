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
struct TYPE_5__ {int /*<<< orphan*/ * y; int /*<<< orphan*/ * g; int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {TYPE_1__ elg; } ;
struct TYPE_7__ {TYPE_2__ pub; } ;
typedef  TYPE_3__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;

/* Variables and functions */
 int PXE_PGP_MATH_FAILED ; 
 int /*<<< orphan*/ * bn_to_mpi (int /*<<< orphan*/ *) ; 
 int decide_k_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_count_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_modmul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_new () ; 
 int mp_px_rand (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpi_to_bn (int /*<<< orphan*/ *) ; 

int
pgp_elgamal_encrypt(PGP_PubKey *pk, PGP_MPI *_m,
					PGP_MPI **c1_p, PGP_MPI **c2_p)
{
	int			res = PXE_PGP_MATH_FAILED;
	int			k_bits;
	mpz_t	   *m = mpi_to_bn(_m);
	mpz_t	   *p = mpi_to_bn(pk->pub.elg.p);
	mpz_t	   *g = mpi_to_bn(pk->pub.elg.g);
	mpz_t	   *y = mpi_to_bn(pk->pub.elg.y);
	mpz_t	   *k = mp_new();
	mpz_t	   *yk = mp_new();
	mpz_t	   *c1 = mp_new();
	mpz_t	   *c2 = mp_new();

	if (!m || !p || !g || !y || !k || !yk || !c1 || !c2)
		goto err;

	/*
	 * generate k
	 */
	k_bits = decide_k_bits(mp_int_count_bits(p));
	res = mp_px_rand(k_bits, k);
	if (res < 0)
		return res;

	/*
	 * c1 = g^k c2 = m * y^k
	 */
	mp_int_exptmod(g, k, p, c1);
	mp_int_exptmod(y, k, p, yk);
	mp_modmul(m, yk, p, c2);

	/* result */
	*c1_p = bn_to_mpi(c1);
	*c2_p = bn_to_mpi(c2);
	if (*c1_p && *c2_p)
		res = 0;
err:
	mp_clear_free(c2);
	mp_clear_free(c1);
	mp_clear_free(yk);
	mp_clear_free(k);
	mp_clear_free(y);
	mp_clear_free(g);
	mp_clear_free(p);
	mp_clear_free(m);
	return res;
}