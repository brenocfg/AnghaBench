#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ typtype; int /*<<< orphan*/  flags; int /*<<< orphan*/  hash_extended_proc; int /*<<< orphan*/  hash_proc; TYPE_1__* rngelemtype; } ;
typedef  TYPE_2__ TypeCacheEntry ;
struct TYPE_6__ {int /*<<< orphan*/  type_id; } ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCFLAGS_CHECKED_ELEM_PROPERTIES ; 
 int /*<<< orphan*/  TCFLAGS_HAVE_ELEM_EXTENDED_HASHING ; 
 int /*<<< orphan*/  TCFLAGS_HAVE_ELEM_HASHING ; 
 int TYPECACHE_HASH_EXTENDED_PROC ; 
 int TYPECACHE_HASH_PROC ; 
 scalar_t__ TYPTYPE_RANGE ; 
 int /*<<< orphan*/  load_rangetype_info (TYPE_2__*) ; 
 TYPE_2__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cache_range_element_properties(TypeCacheEntry *typentry)
{
	/* load up subtype link if we didn't already */
	if (typentry->rngelemtype == NULL &&
		typentry->typtype == TYPTYPE_RANGE)
		load_rangetype_info(typentry);

	if (typentry->rngelemtype != NULL)
	{
		TypeCacheEntry *elementry;

		/* might need to calculate subtype's hash function properties */
		elementry = lookup_type_cache(typentry->rngelemtype->type_id,
									  TYPECACHE_HASH_PROC |
									  TYPECACHE_HASH_EXTENDED_PROC);
		if (OidIsValid(elementry->hash_proc))
			typentry->flags |= TCFLAGS_HAVE_ELEM_HASHING;
		if (OidIsValid(elementry->hash_extended_proc))
			typentry->flags |= TCFLAGS_HAVE_ELEM_EXTENDED_HASHING;
	}
	typentry->flags |= TCFLAGS_CHECKED_ELEM_PROPERTIES;
}