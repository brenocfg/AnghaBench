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
typedef  int /*<<< orphan*/  HASHSEGMENT ;
typedef  int /*<<< orphan*/  HASHHDR ;
typedef  int /*<<< orphan*/  HASHELEMENT ;
typedef  int /*<<< orphan*/  HASHBUCKET ;

/* Variables and functions */
 long DEF_DIRSIZE ; 
 long DEF_FFACTOR ; 
 long DEF_SEGSIZE ; 
 long MAXALIGN (int) ; 
 int add_size (int,long) ; 
 long choose_nelem_alloc (int) ; 
 long mul_size (long,long) ; 
 long next_pow2_long (long) ; 

Size
hash_estimate_size(long num_entries, Size entrysize)
{
	Size		size;
	long		nBuckets,
				nSegments,
				nDirEntries,
				nElementAllocs,
				elementSize,
				elementAllocCnt;

	/* estimate number of buckets wanted */
	nBuckets = next_pow2_long((num_entries - 1) / DEF_FFACTOR + 1);
	/* # of segments needed for nBuckets */
	nSegments = next_pow2_long((nBuckets - 1) / DEF_SEGSIZE + 1);
	/* directory entries */
	nDirEntries = DEF_DIRSIZE;
	while (nDirEntries < nSegments)
		nDirEntries <<= 1;		/* dir_alloc doubles dsize at each call */

	/* fixed control info */
	size = MAXALIGN(sizeof(HASHHDR));	/* but not HTAB, per above */
	/* directory */
	size = add_size(size, mul_size(nDirEntries, sizeof(HASHSEGMENT)));
	/* segments */
	size = add_size(size, mul_size(nSegments,
								   MAXALIGN(DEF_SEGSIZE * sizeof(HASHBUCKET))));
	/* elements --- allocated in groups of choose_nelem_alloc() entries */
	elementAllocCnt = choose_nelem_alloc(entrysize);
	nElementAllocs = (num_entries - 1) / elementAllocCnt + 1;
	elementSize = MAXALIGN(sizeof(HASHELEMENT)) + MAXALIGN(entrysize);
	size = add_size(size,
					mul_size(nElementAllocs,
							 mul_size(elementAllocCnt, elementSize)));

	return size;
}