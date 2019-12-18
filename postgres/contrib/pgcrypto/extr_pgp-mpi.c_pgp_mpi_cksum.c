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
struct TYPE_3__ {int bits; int bytes; scalar_t__* data; } ;
typedef  TYPE_1__ PGP_MPI ;

/* Variables and functions */

unsigned
pgp_mpi_cksum(unsigned cksum, PGP_MPI *n)
{
	int			i;

	cksum += n->bits >> 8;
	cksum += n->bits & 0xFF;
	for (i = 0; i < n->bytes; i++)
		cksum += n->data[i];

	return cksum & 0xFFFF;
}