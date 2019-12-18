#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ n ;
struct TYPE_4__ {int bits; int bytes; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ PGP_MPI ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_DATA ; 
 TYPE_1__* px_alloc (int) ; 
 int /*<<< orphan*/  px_debug (char*,int) ; 

int
pgp_mpi_alloc(int bits, PGP_MPI **mpi)
{
	PGP_MPI    *n;
	int			len = (bits + 7) / 8;

	if (bits < 0 || bits > 0xFFFF)
	{
		px_debug("pgp_mpi_alloc: unreasonable request: bits=%d", bits);
		return PXE_PGP_CORRUPT_DATA;
	}
	n = px_alloc(sizeof(*n) + len);
	n->bits = bits;
	n->bytes = len;
	n->data = (uint8 *) (n) + sizeof(*n);
	*mpi = n;
	return 0;
}