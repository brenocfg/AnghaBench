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
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_3__ {scalar_t__ bits; int /*<<< orphan*/  bytes; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGP_MPI ;

/* Variables and functions */
 int /*<<< orphan*/  mp_clear_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_int_count_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_read_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_new () ; 
 int /*<<< orphan*/  px_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mpz_t *
mpi_to_bn(PGP_MPI *n)
{
	mpz_t	   *bn = mp_new();

	mp_int_read_unsigned(bn, n->data, n->bytes);

	if (!bn)
		return NULL;
	if (mp_int_count_bits(bn) != n->bits)
	{
		px_debug("mpi_to_bn: bignum conversion failed: mpi=%d, bn=%d",
				 n->bits, mp_int_count_bits(bn));
		mp_clear_free(bn);
		return NULL;
	}
	return bn;
}