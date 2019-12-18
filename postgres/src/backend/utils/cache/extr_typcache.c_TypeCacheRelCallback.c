#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ typtype; scalar_t__ typrelid; int flags; scalar_t__ tupDesc_identifier; TYPE_2__* tupDesc; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_4__ {scalar_t__ tdrefcount; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FreeTupleDesc (TYPE_2__*) ; 
 scalar_t__ InvalidOid ; 
 int TCFLAGS_DOMAIN_BASE_IS_COMPOSITE ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  TypeCacheHash ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
TypeCacheRelCallback(Datum arg, Oid relid)
{
	HASH_SEQ_STATUS status;
	TypeCacheEntry *typentry;

	/* TypeCacheHash must exist, else this callback wouldn't be registered */
	hash_seq_init(&status, TypeCacheHash);
	while ((typentry = (TypeCacheEntry *) hash_seq_search(&status)) != NULL)
	{
		if (typentry->typtype == TYPTYPE_COMPOSITE)
		{
			/* Skip if no match, unless we're zapping all composite types */
			if (relid != typentry->typrelid && relid != InvalidOid)
				continue;

			/* Delete tupdesc if we have it */
			if (typentry->tupDesc != NULL)
			{
				/*
				 * Release our refcount, and free the tupdesc if none remain.
				 * (Can't use DecrTupleDescRefCount because this reference is
				 * not logged in current resource owner.)
				 */
				Assert(typentry->tupDesc->tdrefcount > 0);
				if (--typentry->tupDesc->tdrefcount == 0)
					FreeTupleDesc(typentry->tupDesc);
				typentry->tupDesc = NULL;

				/*
				 * Also clear tupDesc_identifier, so that anything watching
				 * that will realize that the tupdesc has possibly changed.
				 * (Alternatively, we could specify that to detect possible
				 * tupdesc change, one must check for tupDesc != NULL as well
				 * as tupDesc_identifier being the same as what was previously
				 * seen.  That seems error-prone.)
				 */
				typentry->tupDesc_identifier = 0;
			}

			/* Reset equality/comparison/hashing validity information */
			typentry->flags = 0;
		}
		else if (typentry->typtype == TYPTYPE_DOMAIN)
		{
			/*
			 * If it's domain over composite, reset flags.  (We don't bother
			 * trying to determine whether the specific base type needs a
			 * reset.)  Note that if we haven't determined whether the base
			 * type is composite, we don't need to reset anything.
			 */
			if (typentry->flags & TCFLAGS_DOMAIN_BASE_IS_COMPOSITE)
				typentry->flags = 0;
		}
	}
}