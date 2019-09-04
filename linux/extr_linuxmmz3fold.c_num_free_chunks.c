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
struct z3fold_header {scalar_t__ middle_chunks; int first_chunks; int start_middle; int last_chunks; } ;

/* Variables and functions */
 int NCHUNKS ; 
 int TOTAL_CHUNKS ; 
 int ZHDR_CHUNKS ; 
 int max (int,int) ; 

__attribute__((used)) static int num_free_chunks(struct z3fold_header *zhdr)
{
	int nfree;
	/*
	 * If there is a middle object, pick up the bigger free space
	 * either before or after it. Otherwise just subtract the number
	 * of chunks occupied by the first and the last objects.
	 */
	if (zhdr->middle_chunks != 0) {
		int nfree_before = zhdr->first_chunks ?
			0 : zhdr->start_middle - ZHDR_CHUNKS;
		int nfree_after = zhdr->last_chunks ?
			0 : TOTAL_CHUNKS -
				(zhdr->start_middle + zhdr->middle_chunks);
		nfree = max(nfree_before, nfree_after);
	} else
		nfree = NCHUNKS - zhdr->first_chunks - zhdr->last_chunks;
	return nfree;
}