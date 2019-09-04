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
typedef  scalar_t__* mpi_ptr_t ;
typedef  scalar_t__ mpi_limb_t ;

/* Variables and functions */

int mpihelp_cmp(mpi_ptr_t op1_ptr, mpi_ptr_t op2_ptr, mpi_size_t size)
{
	mpi_size_t i;
	mpi_limb_t op1_word, op2_word;

	for (i = size - 1; i >= 0; i--) {
		op1_word = op1_ptr[i];
		op2_word = op2_ptr[i];
		if (op1_word != op2_word)
			goto diff;
	}
	return 0;

diff:
	/* This can *not* be simplified to
	 *   op2_word - op2_word
	 * since that expression might give signed overflow.  */
	return (op1_word > op2_word) ? 1 : -1;
}