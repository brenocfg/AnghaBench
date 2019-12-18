#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_5__ {int bytes; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGP_MPI ;

/* Variables and functions */
 int mp_int_count_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_to_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pgp_mpi_alloc (int,TYPE_1__**) ; 
 int /*<<< orphan*/  pgp_mpi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  px_debug (char*,int,int) ; 

__attribute__((used)) static PGP_MPI *
bn_to_mpi(mpz_t *bn)
{
	int			res;
	PGP_MPI    *n;
	int			bytes;

	res = pgp_mpi_alloc(mp_int_count_bits(bn), &n);
	if (res < 0)
		return NULL;

	bytes = (mp_int_count_bits(bn) + 7) / 8;
	if (bytes != n->bytes)
	{
		px_debug("bn_to_mpi: bignum conversion failed: bn=%d, mpi=%d",
				 bytes, n->bytes);
		pgp_mpi_free(n);
		return NULL;
	}
	mp_int_to_unsigned(bn, n->data, n->bytes);
	return n;
}