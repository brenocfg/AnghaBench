#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int entrysize; int /*<<< orphan*/  keysize; } ;
typedef  int /*<<< orphan*/  ShmemIndexEnt ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int HASH_ELEM ; 
 int /*<<< orphan*/  SHMEM_INDEX_KEYSIZE ; 
 int /*<<< orphan*/  SHMEM_INDEX_SIZE ; 
 int /*<<< orphan*/  ShmemIndex ; 
 int /*<<< orphan*/  ShmemInitHash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
InitShmemIndex(void)
{
	HASHCTL		info;
	int			hash_flags;

	/*
	 * Create the shared memory shmem index.
	 *
	 * Since ShmemInitHash calls ShmemInitStruct, which expects the ShmemIndex
	 * hashtable to exist already, we have a bit of a circularity problem in
	 * initializing the ShmemIndex itself.  The special "ShmemIndex" hash
	 * table name will tell ShmemInitStruct to fake it.
	 */
	info.keysize = SHMEM_INDEX_KEYSIZE;
	info.entrysize = sizeof(ShmemIndexEnt);
	hash_flags = HASH_ELEM;

	ShmemIndex = ShmemInitHash("ShmemIndex",
							   SHMEM_INDEX_SIZE, SHMEM_INDEX_SIZE,
							   &info, hash_flags);
}