#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int mpi_size_t ;
typedef  scalar_t__* mpi_ptr_t ;
typedef  scalar_t__ mpi_limb_t ;

/* Variables and functions */

mpi_limb_t
mpihelp_sub_n(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
	      mpi_ptr_t s2_ptr, mpi_size_t size)
{
	mpi_limb_t x, y, cy;
	mpi_size_t j;

	/* The loop counter and index J goes from -SIZE to -1.  This way
	   the loop becomes faster.  */
	j = -size;

	/* Offset the base pointers to compensate for the negative indices.  */
	s1_ptr -= j;
	s2_ptr -= j;
	res_ptr -= j;

	cy = 0;
	do {
		y = s2_ptr[j];
		x = s1_ptr[j];
		y += cy;	/* add previous carry to subtrahend */
		cy = y < cy;	/* get out carry from that addition */
		y = x - y;	/* main subtract */
		cy += y > x;	/* get out carry from the subtract, combine */
		res_ptr[j] = y;
	} while (++j);

	return cy;
}