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
typedef  scalar_t__ uint8_t ;
typedef  int mpi_limb_t ;
struct TYPE_4__ {unsigned int nbits; unsigned int nlimbs; int* d; scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 size_t BYTES_PER_MPI_LIMB ; 
 unsigned int DIV_ROUND_UP (size_t,size_t) ; 
 unsigned int MAX_EXTERN_MPI_BITS ; 
 int count_leading_zeros (scalar_t__ const) ; 
 TYPE_1__* mpi_alloc (unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

MPI mpi_read_raw_data(const void *xbuffer, size_t nbytes)
{
	const uint8_t *buffer = xbuffer;
	int i, j;
	unsigned nbits, nlimbs;
	mpi_limb_t a;
	MPI val = NULL;

	while (nbytes > 0 && buffer[0] == 0) {
		buffer++;
		nbytes--;
	}

	nbits = nbytes * 8;
	if (nbits > MAX_EXTERN_MPI_BITS) {
		pr_info("MPI: mpi too large (%u bits)\n", nbits);
		return NULL;
	}
	if (nbytes > 0)
		nbits -= count_leading_zeros(buffer[0]) - (BITS_PER_LONG - 8);

	nlimbs = DIV_ROUND_UP(nbytes, BYTES_PER_MPI_LIMB);
	val = mpi_alloc(nlimbs);
	if (!val)
		return NULL;
	val->nbits = nbits;
	val->sign = 0;
	val->nlimbs = nlimbs;

	if (nbytes > 0) {
		i = BYTES_PER_MPI_LIMB - nbytes % BYTES_PER_MPI_LIMB;
		i %= BYTES_PER_MPI_LIMB;
		for (j = nlimbs; j > 0; j--) {
			a = 0;
			for (; i < BYTES_PER_MPI_LIMB; i++) {
				a <<= 8;
				a |= *buffer++;
			}
			i = 0;
			val->d[j - 1] = a;
		}
	}
	return val;
}