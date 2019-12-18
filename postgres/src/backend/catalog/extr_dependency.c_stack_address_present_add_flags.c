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
struct TYPE_6__ {scalar_t__ classId; scalar_t__ objectId; scalar_t__ objectSubId; } ;
struct TYPE_5__ {int flags; TYPE_2__* object; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ObjectAddressStack ;
typedef  TYPE_2__ ObjectAddress ;

/* Variables and functions */
 int DEPFLAG_SUBOBJECT ; 

__attribute__((used)) static bool
stack_address_present_add_flags(const ObjectAddress *object,
								int flags,
								ObjectAddressStack *stack)
{
	bool		result = false;
	ObjectAddressStack *stackptr;

	for (stackptr = stack; stackptr; stackptr = stackptr->next)
	{
		const ObjectAddress *thisobj = stackptr->object;

		if (object->classId == thisobj->classId &&
			object->objectId == thisobj->objectId)
		{
			if (object->objectSubId == thisobj->objectSubId)
			{
				stackptr->flags |= flags;
				result = true;
			}
			else if (thisobj->objectSubId == 0)
			{
				/*
				 * We're visiting a column with whole table already on stack.
				 * As in object_address_present_add_flags(), we can skip
				 * further processing of the subobject, but we don't want to
				 * propagate flags for the subobject to the whole object.
				 */
				result = true;
			}
			else if (object->objectSubId == 0)
			{
				/*
				 * We're visiting a table with column already on stack.  As in
				 * object_address_present_add_flags(), we should propagate
				 * flags for the whole object to each of its subobjects.
				 */
				if (flags)
					stackptr->flags |= (flags | DEPFLAG_SUBOBJECT);
			}
		}
	}

	return result;
}