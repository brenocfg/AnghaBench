#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_4__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  RelIdCacheEnt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  INITRELCACHESIZE ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RelationIdCache ; 
 int /*<<< orphan*/  RelationMapInitialize () ; 
 int /*<<< orphan*/  hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
RelationCacheInitialize(void)
{
	HASHCTL		ctl;

	/*
	 * make sure cache memory context exists
	 */
	if (!CacheMemoryContext)
		CreateCacheMemoryContext();

	/*
	 * create hashtable that indexes the relcache
	 */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(Oid);
	ctl.entrysize = sizeof(RelIdCacheEnt);
	RelationIdCache = hash_create("Relcache by OID", INITRELCACHESIZE,
								  &ctl, HASH_ELEM | HASH_BLOBS);

	/*
	 * relation mapper needs to be initialized too
	 */
	RelationMapInitialize();
}