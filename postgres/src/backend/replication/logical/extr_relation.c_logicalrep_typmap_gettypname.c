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
struct TYPE_3__ {int /*<<< orphan*/  typname; int /*<<< orphan*/  nspname; int /*<<< orphan*/  remoteid; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ LogicalRepTyp ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstGenbkiObjectId ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/ * LogicalRepTypMap ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 char* format_type_be (scalar_t__) ; 
 int /*<<< orphan*/  get_typisdefined (scalar_t__) ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 char* psprintf (char*,scalar_t__,...) ; 

char *
logicalrep_typmap_gettypname(Oid remoteid)
{
	LogicalRepTyp *entry;
	bool		found;

	/* Internal types are mapped directly. */
	if (remoteid < FirstGenbkiObjectId)
	{
		if (!get_typisdefined(remoteid))
		{
			/*
			 * This can be caused by having a publisher with a higher
			 * PostgreSQL major version than the subscriber.
			 */
			return psprintf("unrecognized %u", remoteid);
		}

		return format_type_be(remoteid);
	}

	if (LogicalRepTypMap == NULL)
	{
		/*
		 * If the typemap is not initialized yet, we cannot possibly attempt
		 * to search the hash table; but there's no way we know the type
		 * locally yet, since we haven't received a message about this type,
		 * so this is the best we can do.
		 */
		return psprintf("unrecognized %u", remoteid);
	}

	/* search the mapping */
	entry = hash_search(LogicalRepTypMap, (void *) &remoteid,
						HASH_FIND, &found);
	if (!found)
		return psprintf("unrecognized %u", remoteid);

	Assert(OidIsValid(entry->remoteid));
	return psprintf("%s.%s", entry->nspname, entry->typname);
}