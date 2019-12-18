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
typedef  int /*<<< orphan*/  TypeCacheEnumData ;
struct TYPE_6__ {int /*<<< orphan*/  type_id; int /*<<< orphan*/ * enumData; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_7__ {scalar_t__ sort_order; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ EnumItem ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ enum_known_sorted (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* find_enumitem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_enum_cache_data (TYPE_1__*) ; 

int
compare_values_of_enum(TypeCacheEntry *tcache, Oid arg1, Oid arg2)
{
	TypeCacheEnumData *enumdata;
	EnumItem   *item1;
	EnumItem   *item2;

	/*
	 * Equal OIDs are certainly equal --- this case was probably handled by
	 * our caller, but we may as well check.
	 */
	if (arg1 == arg2)
		return 0;

	/* Load up the cache if first time through */
	if (tcache->enumData == NULL)
		load_enum_cache_data(tcache);
	enumdata = tcache->enumData;

	/*
	 * If both OIDs are known-sorted, we can just compare them directly.
	 */
	if (enum_known_sorted(enumdata, arg1) &&
		enum_known_sorted(enumdata, arg2))
	{
		if (arg1 < arg2)
			return -1;
		else
			return 1;
	}

	/*
	 * Slow path: we have to identify their actual sort-order positions.
	 */
	item1 = find_enumitem(enumdata, arg1);
	item2 = find_enumitem(enumdata, arg2);

	if (item1 == NULL || item2 == NULL)
	{
		/*
		 * We couldn't find one or both values.  That means the enum has
		 * changed under us, so re-initialize the cache and try again. We
		 * don't bother retrying the known-sorted case in this path.
		 */
		load_enum_cache_data(tcache);
		enumdata = tcache->enumData;

		item1 = find_enumitem(enumdata, arg1);
		item2 = find_enumitem(enumdata, arg2);

		/*
		 * If we still can't find the values, complain: we must have corrupt
		 * data.
		 */
		if (item1 == NULL)
			elog(ERROR, "enum value %u not found in cache for enum %s",
				 arg1, format_type_be(tcache->type_id));
		if (item2 == NULL)
			elog(ERROR, "enum value %u not found in cache for enum %s",
				 arg2, format_type_be(tcache->type_id));
	}

	if (item1->sort_order < item2->sort_order)
		return -1;
	else if (item1->sort_order > item2->sort_order)
		return 1;
	else
		return 0;
}