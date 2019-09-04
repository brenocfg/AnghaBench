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
typedef  scalar_t__ mpi_limb_t ;
struct TYPE_3__ {int nlimbs; scalar_t__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int count_leading_zeros (scalar_t__) ; 

__attribute__((used)) static int count_lzeros(MPI a)
{
	mpi_limb_t alimb;
	int i, lzeros = 0;

	for (i = a->nlimbs - 1; i >= 0; i--) {
		alimb = a->d[i];
		if (alimb == 0) {
			lzeros += sizeof(mpi_limb_t);
		} else {
			lzeros += count_leading_zeros(alimb) / 8;
			break;
		}
	}
	return lzeros;
}