#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_6__ {int keysize; int entrysize; } ;
struct TYPE_5__ {int /*<<< orphan*/  opr_oid; } ;
typedef  int /*<<< orphan*/  OprCacheKey ;
typedef  TYPE_1__ OprCacheEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ HASHCTL ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CASTSOURCETARGET ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvalidateOprCacheCallBack ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OPERNAMENSP ; 
 int /*<<< orphan*/ * OprCacheHash ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_2__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
find_oper_cache_entry(OprCacheKey *key)
{
	OprCacheEntry *oprentry;

	if (OprCacheHash == NULL)
	{
		/* First time through: initialize the hash table */
		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(OprCacheKey);
		ctl.entrysize = sizeof(OprCacheEntry);
		OprCacheHash = hash_create("Operator lookup cache", 256,
								   &ctl, HASH_ELEM | HASH_BLOBS);

		/* Arrange to flush cache on pg_operator and pg_cast changes */
		CacheRegisterSyscacheCallback(OPERNAMENSP,
									  InvalidateOprCacheCallBack,
									  (Datum) 0);
		CacheRegisterSyscacheCallback(CASTSOURCETARGET,
									  InvalidateOprCacheCallBack,
									  (Datum) 0);
	}

	/* Look for an existing entry */
	oprentry = (OprCacheEntry *) hash_search(OprCacheHash,
											 (void *) key,
											 HASH_FIND, NULL);
	if (oprentry == NULL)
		return InvalidOid;

	return oprentry->opr_oid;
}