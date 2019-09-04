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
struct rds_iovec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int rds_pages_in_vec (struct rds_iovec*) ; 

__attribute__((used)) static int rds_rdma_pages(struct rds_iovec iov[], int nr_iovecs)
{
	int tot_pages = 0;
	unsigned int nr_pages;
	unsigned int i;

	/* figure out the number of pages in the vector */
	for (i = 0; i < nr_iovecs; i++) {
		nr_pages = rds_pages_in_vec(&iov[i]);
		if (nr_pages == 0)
			return -EINVAL;

		tot_pages += nr_pages;

		/*
		 * nr_pages for one entry is limited to (UINT_MAX>>PAGE_SHIFT)+1,
		 * so tot_pages cannot overflow without first going negative.
		 */
		if (tot_pages < 0)
			return -EINVAL;
	}

	return tot_pages;
}