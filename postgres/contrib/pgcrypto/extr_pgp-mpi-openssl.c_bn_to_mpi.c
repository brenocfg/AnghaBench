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
struct TYPE_5__ {scalar_t__ bytes; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGP_MPI ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_num_bytes (int /*<<< orphan*/ *) ; 
 int pgp_mpi_alloc (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  pgp_mpi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  px_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static PGP_MPI *
bn_to_mpi(BIGNUM *bn)
{
	int			res;
	PGP_MPI    *n;

	res = pgp_mpi_alloc(BN_num_bits(bn), &n);
	if (res < 0)
		return NULL;

	if (BN_num_bytes(bn) != n->bytes)
	{
		px_debug("bn_to_mpi: bignum conversion failed: bn=%d, mpi=%d",
				 BN_num_bytes(bn), n->bytes);
		pgp_mpi_free(n);
		return NULL;
	}
	BN_bn2bin(bn, n->data);
	return n;
}