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
typedef  int Size ;
typedef  int /*<<< orphan*/  HASHELEMENT ;

/* Variables and functions */
 int MAXALIGN (int) ; 

__attribute__((used)) static int
choose_nelem_alloc(Size entrysize)
{
	int			nelem_alloc;
	Size		elementSize;
	Size		allocSize;

	/* Each element has a HASHELEMENT header plus user data. */
	/* NB: this had better match element_alloc() */
	elementSize = MAXALIGN(sizeof(HASHELEMENT)) + MAXALIGN(entrysize);

	/*
	 * The idea here is to choose nelem_alloc at least 32, but round up so
	 * that the allocation request will be a power of 2 or just less. This
	 * makes little difference for hash tables in shared memory, but for hash
	 * tables managed by palloc, the allocation request will be rounded up to
	 * a power of 2 anyway.  If we fail to take this into account, we'll waste
	 * as much as half the allocated space.
	 */
	allocSize = 32 * 4;			/* assume elementSize at least 8 */
	do
	{
		allocSize <<= 1;
		nelem_alloc = allocSize / elementSize;
	} while (nelem_alloc < 32);

	return nelem_alloc;
}