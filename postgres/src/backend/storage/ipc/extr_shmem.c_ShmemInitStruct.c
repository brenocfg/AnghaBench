#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * index; } ;
struct TYPE_4__ {scalar_t__ size; void* location; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__ ShmemIndexEnt ;
typedef  TYPE_2__ PGShmemHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHELINEALIGN (void*) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER_NULL ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int ShmemAddrIsValid (void*) ; 
 void* ShmemAlloc (scalar_t__) ; 
 void* ShmemAllocNoError (scalar_t__) ; 
 int /*<<< orphan*/  ShmemIndex ; 
 int /*<<< orphan*/  ShmemIndexLock ; 
 TYPE_2__* ShmemSegHdr ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void *
ShmemInitStruct(const char *name, Size size, bool *foundPtr)
{
	ShmemIndexEnt *result;
	void	   *structPtr;

	LWLockAcquire(ShmemIndexLock, LW_EXCLUSIVE);

	if (!ShmemIndex)
	{
		PGShmemHeader *shmemseghdr = ShmemSegHdr;

		/* Must be trying to create/attach to ShmemIndex itself */
		Assert(strcmp(name, "ShmemIndex") == 0);

		if (IsUnderPostmaster)
		{
			/* Must be initializing a (non-standalone) backend */
			Assert(shmemseghdr->index != NULL);
			structPtr = shmemseghdr->index;
			*foundPtr = true;
		}
		else
		{
			/*
			 * If the shmem index doesn't exist, we are bootstrapping: we must
			 * be trying to init the shmem index itself.
			 *
			 * Notice that the ShmemIndexLock is released before the shmem
			 * index has been initialized.  This should be OK because no other
			 * process can be accessing shared memory yet.
			 */
			Assert(shmemseghdr->index == NULL);
			structPtr = ShmemAlloc(size);
			shmemseghdr->index = structPtr;
			*foundPtr = false;
		}
		LWLockRelease(ShmemIndexLock);
		return structPtr;
	}

	/* look it up in the shmem index */
	result = (ShmemIndexEnt *)
		hash_search(ShmemIndex, name, HASH_ENTER_NULL, foundPtr);

	if (!result)
	{
		LWLockRelease(ShmemIndexLock);
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("could not create ShmemIndex entry for data structure \"%s\"",
						name)));
	}

	if (*foundPtr)
	{
		/*
		 * Structure is in the shmem index so someone else has allocated it
		 * already.  The size better be the same as the size we are trying to
		 * initialize to, or there is a name conflict (or worse).
		 */
		if (result->size != size)
		{
			LWLockRelease(ShmemIndexLock);
			ereport(ERROR,
					(errmsg("ShmemIndex entry size is wrong for data structure"
							" \"%s\": expected %zu, actual %zu",
							name, size, result->size)));
		}
		structPtr = result->location;
	}
	else
	{
		/* It isn't in the table yet. allocate and initialize it */
		structPtr = ShmemAllocNoError(size);
		if (structPtr == NULL)
		{
			/* out of memory; remove the failed ShmemIndex entry */
			hash_search(ShmemIndex, name, HASH_REMOVE, NULL);
			LWLockRelease(ShmemIndexLock);
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("not enough shared memory for data structure"
							" \"%s\" (%zu bytes requested)",
							name, size)));
		}
		result->size = size;
		result->location = structPtr;
	}

	LWLockRelease(ShmemIndexLock);

	Assert(ShmemAddrIsValid(structPtr));

	Assert(structPtr == (void *) CACHELINEALIGN(structPtr));

	return structPtr;
}