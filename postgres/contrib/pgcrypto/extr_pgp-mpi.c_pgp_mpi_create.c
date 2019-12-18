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
struct TYPE_4__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGP_MPI ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pgp_mpi_alloc (int,TYPE_1__**) ; 

int
pgp_mpi_create(uint8 *data, int bits, PGP_MPI **mpi)
{
	int			res;
	PGP_MPI    *n;

	res = pgp_mpi_alloc(bits, &n);
	if (res < 0)
		return res;
	memcpy(n->data, data, n->bytes);
	*mpi = n;
	return 0;
}