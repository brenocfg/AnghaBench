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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  LWLockMinimallyPadded ;
typedef  int /*<<< orphan*/  CkptSortItem ;
typedef  int /*<<< orphan*/  BufferDescPadded ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  NBuffers ; 
 int /*<<< orphan*/  PG_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  StrategyShmemSize () ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (int /*<<< orphan*/ ,int) ; 

Size
BufferShmemSize(void)
{
	Size		size = 0;

	/* size of buffer descriptors */
	size = add_size(size, mul_size(NBuffers, sizeof(BufferDescPadded)));
	/* to allow aligning buffer descriptors */
	size = add_size(size, PG_CACHE_LINE_SIZE);

	/* size of data pages */
	size = add_size(size, mul_size(NBuffers, BLCKSZ));

	/* size of stuff controlled by freelist.c */
	size = add_size(size, StrategyShmemSize());

	/*
	 * It would be nice to include the I/O locks in the BufferDesc, but that
	 * would increase the size of a BufferDesc to more than one cache line,
	 * and benchmarking has shown that keeping every BufferDesc aligned on a
	 * cache line boundary is important for performance.  So, instead, the
	 * array of I/O locks is allocated in a separate tranche.  Because those
	 * locks are not highly contended, we lay out the array with minimal
	 * padding.
	 */
	size = add_size(size, mul_size(NBuffers, sizeof(LWLockMinimallyPadded)));
	/* to allow aligning the above */
	size = add_size(size, PG_CACHE_LINE_SIZE);

	/* size of checkpoint sort array in bufmgr.c */
	size = add_size(size, mul_size(NBuffers, sizeof(CkptSortItem)));

	return size;
}