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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int MAX_EXTERN_MPI_BITS ; 
 int /*<<< orphan*/  mpi_read_raw_data (int const*,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,...) ; 

MPI mpi_read_from_buffer(const void *xbuffer, unsigned *ret_nread)
{
	const uint8_t *buffer = xbuffer;
	unsigned int nbits, nbytes;
	MPI val;

	if (*ret_nread < 2)
		return ERR_PTR(-EINVAL);
	nbits = buffer[0] << 8 | buffer[1];

	if (nbits > MAX_EXTERN_MPI_BITS) {
		pr_info("MPI: mpi too large (%u bits)\n", nbits);
		return ERR_PTR(-EINVAL);
	}

	nbytes = DIV_ROUND_UP(nbits, 8);
	if (nbytes + 2 > *ret_nread) {
		pr_info("MPI: mpi larger than buffer nbytes=%u ret_nread=%u\n",
				nbytes, *ret_nread);
		return ERR_PTR(-EINVAL);
	}

	val = mpi_read_raw_data(buffer + 2, nbytes);
	if (!val)
		return ERR_PTR(-ENOMEM);

	*ret_nread = nbytes + 2;
	return val;
}