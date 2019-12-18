#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_8__ {int flags_valid; int collate_is_c; int ctype_is_c; scalar_t__ locale; } ;
typedef  TYPE_1__ collation_cache_entry ;
struct TYPE_10__ {int /*<<< orphan*/  collctype; int /*<<< orphan*/  collcollate; } ;
struct TYPE_9__ {int keysize; int entrysize; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ HASHCTL ;
typedef  TYPE_3__* Form_pg_collation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COLLOID ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * collation_cache ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_2__*,int) ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static collation_cache_entry *
lookup_collation_cache(Oid collation, bool set_flags)
{
	collation_cache_entry *cache_entry;
	bool		found;

	Assert(OidIsValid(collation));
	Assert(collation != DEFAULT_COLLATION_OID);

	if (collation_cache == NULL)
	{
		/* First time through, initialize the hash table */
		HASHCTL		ctl;

		memset(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(Oid);
		ctl.entrysize = sizeof(collation_cache_entry);
		collation_cache = hash_create("Collation cache", 100, &ctl,
									  HASH_ELEM | HASH_BLOBS);
	}

	cache_entry = hash_search(collation_cache, &collation, HASH_ENTER, &found);
	if (!found)
	{
		/*
		 * Make sure cache entry is marked invalid, in case we fail before
		 * setting things.
		 */
		cache_entry->flags_valid = false;
		cache_entry->locale = 0;
	}

	if (set_flags && !cache_entry->flags_valid)
	{
		/* Attempt to set the flags */
		HeapTuple	tp;
		Form_pg_collation collform;
		const char *collcollate;
		const char *collctype;

		tp = SearchSysCache1(COLLOID, ObjectIdGetDatum(collation));
		if (!HeapTupleIsValid(tp))
			elog(ERROR, "cache lookup failed for collation %u", collation);
		collform = (Form_pg_collation) GETSTRUCT(tp);

		collcollate = NameStr(collform->collcollate);
		collctype = NameStr(collform->collctype);

		cache_entry->collate_is_c = ((strcmp(collcollate, "C") == 0) ||
									 (strcmp(collcollate, "POSIX") == 0));
		cache_entry->ctype_is_c = ((strcmp(collctype, "C") == 0) ||
								   (strcmp(collctype, "POSIX") == 0));

		cache_entry->flags_valid = true;

		ReleaseSysCache(tp);
	}

	return cache_entry;
}