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
typedef  int* mpi_ptr_t ;
typedef  int mpi_limb_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPN_COPY (int*,int*,size_t) ; 
 int /*<<< orphan*/  MPN_ZERO (int*,size_t) ; 
 int mpihelp_add_n (int*,int*,int*,size_t) ; 
 int mpihelp_addmul_1 (int*,int*,size_t,int) ; 
 int mpihelp_mul_1 (int*,int*,size_t,int) ; 

void mpih_sqr_n_basecase(mpi_ptr_t prodp, mpi_ptr_t up, mpi_size_t size)
{
	mpi_size_t i;
	mpi_limb_t cy_limb;
	mpi_limb_t v_limb;

	/* Multiply by the first limb in V separately, as the result can be
	 * stored (not added) to PROD.  We also avoid a loop for zeroing.  */
	v_limb = up[0];
	if (v_limb <= 1) {
		if (v_limb == 1)
			MPN_COPY(prodp, up, size);
		else
			MPN_ZERO(prodp, size);
		cy_limb = 0;
	} else
		cy_limb = mpihelp_mul_1(prodp, up, size, v_limb);

	prodp[size] = cy_limb;
	prodp++;

	/* For each iteration in the outer loop, multiply one limb from
	 * U with one limb from V, and add it to PROD.  */
	for (i = 1; i < size; i++) {
		v_limb = up[i];
		if (v_limb <= 1) {
			cy_limb = 0;
			if (v_limb == 1)
				cy_limb = mpihelp_add_n(prodp, prodp, up, size);
		} else
			cy_limb = mpihelp_addmul_1(prodp, up, size, v_limb);

		prodp[size] = cy_limb;
		prodp++;
	}
}