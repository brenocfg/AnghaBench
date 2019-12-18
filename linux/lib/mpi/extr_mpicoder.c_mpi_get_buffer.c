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
typedef  void uint8_t ;
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int mpi_get_size (int /*<<< orphan*/ ) ; 
 int mpi_read_buffer (int /*<<< orphan*/ ,void*,unsigned int,unsigned int*,int*) ; 

void *mpi_get_buffer(MPI a, unsigned *nbytes, int *sign)
{
	uint8_t *buf;
	unsigned int n;
	int ret;

	if (!nbytes)
		return NULL;

	n = mpi_get_size(a);

	if (!n)
		n++;

	buf = kmalloc(n, GFP_KERNEL);

	if (!buf)
		return NULL;

	ret = mpi_read_buffer(a, buf, n, nbytes, sign);

	if (ret) {
		kfree(buf);
		return NULL;
	}
	return buf;
}