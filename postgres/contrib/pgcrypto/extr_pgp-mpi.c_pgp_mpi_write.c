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
typedef  int uint8 ;
struct TYPE_3__ {int bits; int* data; int bytes; } ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  TYPE_1__ PGP_MPI ;

/* Variables and functions */
 int pushf_write (int /*<<< orphan*/ *,int*,int) ; 

int
pgp_mpi_write(PushFilter *dst, PGP_MPI *n)
{
	int			res;
	uint8		buf[2];

	buf[0] = n->bits >> 8;
	buf[1] = n->bits & 0xFF;
	res = pushf_write(dst, buf, 2);
	if (res >= 0)
		res = pushf_write(dst, n->data, n->bytes);
	return res;
}