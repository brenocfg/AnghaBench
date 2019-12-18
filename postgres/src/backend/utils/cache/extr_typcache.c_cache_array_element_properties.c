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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  hash_extended_proc; int /*<<< orphan*/  hash_proc; int /*<<< orphan*/  cmp_proc; int /*<<< orphan*/  eq_opr; int /*<<< orphan*/  type_id; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCFLAGS_CHECKED_ELEM_PROPERTIES ; 
 int /*<<< orphan*/  TCFLAGS_HAVE_ELEM_COMPARE ; 
 int /*<<< orphan*/  TCFLAGS_HAVE_ELEM_EQUALITY ; 
 int /*<<< orphan*/  TCFLAGS_HAVE_ELEM_EXTENDED_HASHING ; 
 int /*<<< orphan*/  TCFLAGS_HAVE_ELEM_HASHING ; 
 int TYPECACHE_CMP_PROC ; 
 int TYPECACHE_EQ_OPR ; 
 int TYPECACHE_HASH_EXTENDED_PROC ; 
 int TYPECACHE_HASH_PROC ; 
 int /*<<< orphan*/  get_base_element_type (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cache_array_element_properties(TypeCacheEntry *typentry)
{
	Oid			elem_type = get_base_element_type(typentry->type_id);

	if (OidIsValid(elem_type))
	{
		TypeCacheEntry *elementry;

		elementry = lookup_type_cache(elem_type,
									  TYPECACHE_EQ_OPR |
									  TYPECACHE_CMP_PROC |
									  TYPECACHE_HASH_PROC |
									  TYPECACHE_HASH_EXTENDED_PROC);
		if (OidIsValid(elementry->eq_opr))
			typentry->flags |= TCFLAGS_HAVE_ELEM_EQUALITY;
		if (OidIsValid(elementry->cmp_proc))
			typentry->flags |= TCFLAGS_HAVE_ELEM_COMPARE;
		if (OidIsValid(elementry->hash_proc))
			typentry->flags |= TCFLAGS_HAVE_ELEM_HASHING;
		if (OidIsValid(elementry->hash_extended_proc))
			typentry->flags |= TCFLAGS_HAVE_ELEM_EXTENDED_HASHING;
	}
	typentry->flags |= TCFLAGS_CHECKED_ELEM_PROPERTIES;
}