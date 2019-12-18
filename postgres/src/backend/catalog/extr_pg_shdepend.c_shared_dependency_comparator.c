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
struct TYPE_3__ {scalar_t__ objectId; scalar_t__ classId; scalar_t__ objectSubId; } ;
struct TYPE_4__ {scalar_t__ deptype; TYPE_1__ object; } ;
typedef  TYPE_2__ ShDependObjectInfo ;

/* Variables and functions */

__attribute__((used)) static int
shared_dependency_comparator(const void *a, const void *b)
{
	const ShDependObjectInfo *obja = (const ShDependObjectInfo *) a;
	const ShDependObjectInfo *objb = (const ShDependObjectInfo *) b;

	/*
	 * Primary sort key is OID ascending.
	 */
	if (obja->object.objectId < objb->object.objectId)
		return -1;
	if (obja->object.objectId > objb->object.objectId)
		return 1;

	/*
	 * Next sort on catalog ID, in case identical OIDs appear in different
	 * catalogs.  Sort direction is pretty arbitrary here.
	 */
	if (obja->object.classId < objb->object.classId)
		return -1;
	if (obja->object.classId > objb->object.classId)
		return 1;

	/*
	 * Sort on object subId.
	 *
	 * We sort the subId as an unsigned int so that 0 (the whole object) will
	 * come first.
	 */
	if ((unsigned int) obja->object.objectSubId < (unsigned int) objb->object.objectSubId)
		return -1;
	if ((unsigned int) obja->object.objectSubId > (unsigned int) objb->object.objectSubId)
		return 1;

	/*
	 * Last, sort on deptype, in case the same object has multiple dependency
	 * types.  (Note that there's no need to consider objtype, as that's
	 * determined by the catalog OID.)
	 */
	if (obja->deptype < objb->deptype)
		return -1;
	if (obja->deptype > objb->deptype)
		return 1;

	return 0;
}