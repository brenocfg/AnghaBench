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
typedef  size_t mpi_size_t ;
typedef  unsigned int* mpi_ptr_t ;
typedef  unsigned int mpi_limb_t ;

/* Variables and functions */
 unsigned int BITS_PER_MPI_LIMB ; 

mpi_limb_t
mpihelp_rshift(mpi_ptr_t wp, mpi_ptr_t up, mpi_size_t usize, unsigned cnt)
{
	mpi_limb_t high_limb, low_limb;
	unsigned sh_1, sh_2;
	mpi_size_t i;
	mpi_limb_t retval;

	sh_1 = cnt;
	wp -= 1;
	sh_2 = BITS_PER_MPI_LIMB - sh_1;
	high_limb = up[0];
	retval = high_limb << sh_2;
	low_limb = high_limb;
	for (i = 1; i < usize; i++) {
		high_limb = up[i];
		wp[i] = (low_limb >> sh_1) | (high_limb << sh_2);
		low_limb = high_limb;
	}
	wp[i] = low_limb >> sh_1;

	return retval;
}