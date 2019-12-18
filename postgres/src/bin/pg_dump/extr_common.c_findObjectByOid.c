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
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {TYPE_1__ catId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ DumpableObject ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DumpableObject *
findObjectByOid(Oid oid, DumpableObject **indexArray, int numObjs)
{
	DumpableObject **low;
	DumpableObject **high;

	/*
	 * This is the same as findObjectByCatalogId except we assume we need not
	 * look at table OID because the objects are all the same type.
	 *
	 * We could use bsearch() here, but the notational cruft of calling
	 * bsearch is nearly as bad as doing it ourselves; and the generalized
	 * bsearch function is noticeably slower as well.
	 */
	if (numObjs <= 0)
		return NULL;
	low = indexArray;
	high = indexArray + (numObjs - 1);
	while (low <= high)
	{
		DumpableObject **middle;
		int			difference;

		middle = low + (high - low) / 2;
		difference = oidcmp((*middle)->catId.oid, oid);
		if (difference == 0)
			return *middle;
		else if (difference < 0)
			low = middle + 1;
		else
			high = middle - 1;
	}
	return NULL;
}