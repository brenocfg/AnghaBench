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
 int /*<<< orphan*/  umul_ppmm (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

mpi_limb_t
mpihelp_submul_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
		 mpi_size_t s1_size, mpi_limb_t s2_limb)
{
	mpi_limb_t cy_limb;
	mpi_size_t j;
	mpi_limb_t prod_high, prod_low;
	mpi_limb_t x;

	/* The loop counter and index J goes from -SIZE to -1.  This way
	 * the loop becomes faster.  */
	j = -s1_size;
	res_ptr -= j;
	s1_ptr -= j;

	cy_limb = 0;
	do {
		umul_ppmm(prod_high, prod_low, s1_ptr[j], s2_limb);

		prod_low += cy_limb;
		cy_limb = (prod_low < cy_limb ? 1 : 0) + prod_high;

		x = res_ptr[j];
		prod_low = x - prod_low;
		cy_limb += prod_low > x ? 1 : 0;
		res_ptr[j] = prod_low;
	} while (++j);

	return cy_limb;
}