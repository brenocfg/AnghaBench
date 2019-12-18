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
typedef  int /*<<< orphan*/  RelMapFile ;

/* Variables and functions */
 int /*<<< orphan*/  DatabasePath ; 
 int /*<<< orphan*/  GLOBALTABLESPACE_OID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  MyDatabaseTableSpace ; 
 int /*<<< orphan*/  RelationMappingLock ; 
 int /*<<< orphan*/  allowSystemTableMods ; 
 int /*<<< orphan*/  load_relmap_file (int) ; 
 int /*<<< orphan*/  local_map ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  merge_map_updates (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_map ; 
 int /*<<< orphan*/  write_relmap_file (int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
perform_relmap_update(bool shared, const RelMapFile *updates)
{
	RelMapFile	newmap;

	/*
	 * Anyone updating a relation's mapping info should take exclusive lock on
	 * that rel and hold it until commit.  This ensures that there will not be
	 * concurrent updates on the same mapping value; but there could easily be
	 * concurrent updates on different values in the same file. We cover that
	 * by acquiring the RelationMappingLock, re-reading the target file to
	 * ensure it's up to date, applying the updates, and writing the data
	 * before releasing RelationMappingLock.
	 *
	 * There is only one RelationMappingLock.  In principle we could try to
	 * have one per mapping file, but it seems unlikely to be worth the
	 * trouble.
	 */
	LWLockAcquire(RelationMappingLock, LW_EXCLUSIVE);

	/* Be certain we see any other updates just made */
	load_relmap_file(shared);

	/* Prepare updated data in a local variable */
	if (shared)
		memcpy(&newmap, &shared_map, sizeof(RelMapFile));
	else
		memcpy(&newmap, &local_map, sizeof(RelMapFile));

	/*
	 * Apply the updates to newmap.  No new mappings should appear, unless
	 * somebody is adding indexes to system catalogs.
	 */
	merge_map_updates(&newmap, updates, allowSystemTableMods);

	/* Write out the updated map and do other necessary tasks */
	write_relmap_file(shared, &newmap, true, true, true,
					  (shared ? InvalidOid : MyDatabaseId),
					  (shared ? GLOBALTABLESPACE_OID : MyDatabaseTableSpace),
					  DatabasePath);

	/* Now we can release the lock */
	LWLockRelease(RelationMappingLock);
}