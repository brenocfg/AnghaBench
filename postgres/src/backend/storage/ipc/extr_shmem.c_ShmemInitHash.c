#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hctl; int /*<<< orphan*/  alloc; int /*<<< orphan*/  max_dsize; int /*<<< orphan*/  dsize; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASHHDR ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int HASH_ALLOC ; 
 int HASH_ATTACH ; 
 int HASH_DIRSIZE ; 
 int HASH_SHARED_MEM ; 
 int /*<<< orphan*/  ShmemAllocNoError ; 
 void* ShmemInitStruct (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * hash_create (char const*,long,TYPE_1__*,int) ; 
 int /*<<< orphan*/  hash_get_shared_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hash_select_dirsize (long) ; 

HTAB *
ShmemInitHash(const char *name,		/* table string name for shmem index */
			  long init_size,	/* initial table size */
			  long max_size,	/* max size of the table */
			  HASHCTL *infoP,	/* info about key and bucket size */
			  int hash_flags)	/* info about infoP */
{
	bool		found;
	void	   *location;

	/*
	 * Hash tables allocated in shared memory have a fixed directory; it can't
	 * grow or other backends wouldn't be able to find it. So, make sure we
	 * make it big enough to start with.
	 *
	 * The shared memory allocator must be specified too.
	 */
	infoP->dsize = infoP->max_dsize = hash_select_dirsize(max_size);
	infoP->alloc = ShmemAllocNoError;
	hash_flags |= HASH_SHARED_MEM | HASH_ALLOC | HASH_DIRSIZE;

	/* look it up in the shmem index */
	location = ShmemInitStruct(name,
							   hash_get_shared_size(infoP, hash_flags),
							   &found);

	/*
	 * if it already exists, attach to it rather than allocate and initialize
	 * new space
	 */
	if (found)
		hash_flags |= HASH_ATTACH;

	/* Pass location of hashtable header to hash_create */
	infoP->hctl = (HASHHDR *) location;

	return hash_create(name, init_size, infoP, hash_flags);
}