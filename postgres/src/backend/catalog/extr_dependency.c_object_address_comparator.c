#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ objectId; scalar_t__ classId; scalar_t__ objectSubId; } ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */

__attribute__((used)) static int
object_address_comparator(const void *a, const void *b)
{
	const ObjectAddress *obja = (const ObjectAddress *) a;
	const ObjectAddress *objb = (const ObjectAddress *) b;

	/*
	 * Primary sort key is OID descending.  Most of the time, this will result
	 * in putting newer objects before older ones, which is likely to be the
	 * right order to delete in.
	 */
	if (obja->objectId > objb->objectId)
		return -1;
	if (obja->objectId < objb->objectId)
		return 1;

	/*
	 * Next sort on catalog ID, in case identical OIDs appear in different
	 * catalogs.  Sort direction is pretty arbitrary here.
	 */
	if (obja->classId < objb->classId)
		return -1;
	if (obja->classId > objb->classId)
		return 1;

	/*
	 * Last, sort on object subId.
	 *
	 * We sort the subId as an unsigned int so that 0 (the whole object) will
	 * come first.  This is essential for eliminate_duplicate_dependencies,
	 * and is also the best order for findDependentObjects.
	 */
	if ((unsigned int) obja->objectSubId < (unsigned int) objb->objectSubId)
		return -1;
	if ((unsigned int) obja->objectSubId > (unsigned int) objb->objectSubId)
		return 1;
	return 0;
}