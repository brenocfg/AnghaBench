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

/* Variables and functions */
 int /*<<< orphan*/  MADV_REMOVE ; 
 scalar_t__ madvise (char*,int,int /*<<< orphan*/ ) ; 
 int nr_pages ; 
 int page_size ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int shmem_release_pages(char *rel_area)
{
	int ret = 0;

	if (madvise(rel_area, nr_pages * page_size, MADV_REMOVE)) {
		perror("madvise");
		ret = 1;
	}

	return ret;
}