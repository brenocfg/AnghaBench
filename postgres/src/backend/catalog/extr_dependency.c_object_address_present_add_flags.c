#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ classId; scalar_t__ objectId; scalar_t__ objectSubId; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int numrefs; TYPE_2__* extras; TYPE_3__* refs; } ;
typedef  TYPE_1__ ObjectAddresses ;
typedef  TYPE_2__ ObjectAddressExtra ;
typedef  TYPE_3__ ObjectAddress ;

/* Variables and functions */
 int DEPFLAG_SUBOBJECT ; 

__attribute__((used)) static bool
object_address_present_add_flags(const ObjectAddress *object,
								 int flags,
								 ObjectAddresses *addrs)
{
	bool		result = false;
	int			i;

	for (i = addrs->numrefs - 1; i >= 0; i--)
	{
		ObjectAddress *thisobj = addrs->refs + i;

		if (object->classId == thisobj->classId &&
			object->objectId == thisobj->objectId)
		{
			if (object->objectSubId == thisobj->objectSubId)
			{
				ObjectAddressExtra *thisextra = addrs->extras + i;

				thisextra->flags |= flags;
				result = true;
			}
			else if (thisobj->objectSubId == 0)
			{
				/*
				 * We get here if we find a need to delete a column after
				 * having already decided to drop its whole table.  Obviously
				 * we no longer need to drop the subobject, so report that we
				 * found the subobject in the array.  But don't plaster its
				 * flags on the whole object.
				 */
				result = true;
			}
			else if (object->objectSubId == 0)
			{
				/*
				 * We get here if we find a need to delete a whole table after
				 * having already decided to drop one of its columns.  We
				 * can't report that the whole object is in the array, but we
				 * should mark the subobject with the whole object's flags.
				 *
				 * It might seem attractive to physically delete the column's
				 * array entry, or at least mark it as no longer needing
				 * separate deletion.  But that could lead to, e.g., dropping
				 * the column's datatype before we drop the table, which does
				 * not seem like a good idea.  This is a very rare situation
				 * in practice, so we just take the hit of doing a separate
				 * DROP COLUMN action even though we know we're gonna delete
				 * the table later.
				 *
				 * What we can do, though, is mark this as a subobject so that
				 * we don't report it separately, which is confusing because
				 * it's unpredictable whether it happens or not.  But do so
				 * only if flags != 0 (flags == 0 is a read-only probe).
				 *
				 * Because there could be other subobjects of this object in
				 * the array, this case means we always have to loop through
				 * the whole array; we cannot exit early on a match.
				 */
				ObjectAddressExtra *thisextra = addrs->extras + i;

				if (flags)
					thisextra->flags |= (flags | DEPFLAG_SUBOBJECT);
			}
		}
	}

	return result;
}