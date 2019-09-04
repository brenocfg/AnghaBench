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
typedef  scalar_t__ mpi_size_t ;
struct TYPE_5__ {scalar_t__ nlimbs; scalar_t__ sign; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int /*<<< orphan*/  mpi_normalize (TYPE_1__*) ; 
 int mpihelp_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int mpi_cmp(MPI u, MPI v)
{
	mpi_size_t usize, vsize;
	int cmp;

	mpi_normalize(u);
	mpi_normalize(v);
	usize = u->nlimbs;
	vsize = v->nlimbs;
	if (!u->sign && v->sign)
		return 1;
	if (u->sign && !v->sign)
		return -1;
	if (usize != vsize && !u->sign && !v->sign)
		return usize - vsize;
	if (usize != vsize && u->sign && v->sign)
		return vsize - usize;
	if (!usize)
		return 0;
	cmp = mpihelp_cmp(u->d, v->d, usize);
	if (u->sign)
		return -cmp;
	return cmp;
}