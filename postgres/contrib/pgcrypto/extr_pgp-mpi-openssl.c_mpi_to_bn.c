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
struct TYPE_3__ {scalar_t__ bits; int /*<<< orphan*/  bytes; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGP_MPI ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static BIGNUM *
mpi_to_bn(PGP_MPI *n)
{
	BIGNUM	   *bn = BN_bin2bn(n->data, n->bytes, NULL);

	if (!bn)
		return NULL;
	if (BN_num_bits(bn) != n->bits)
	{
		px_debug("mpi_to_bn: bignum conversion failed: mpi=%d, bn=%d",
				 n->bits, BN_num_bits(bn));
		BN_clear_free(bn);
		return NULL;
	}
	return bn;
}