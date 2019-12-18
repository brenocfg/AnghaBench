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
struct TYPE_8__ {int /*<<< orphan*/  tableoid; int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  tableoid; int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ext; TYPE_1__ catId; } ;
typedef  TYPE_2__ ExtensionMemberId ;
typedef  int /*<<< orphan*/  ExtensionInfo ;
typedef  TYPE_3__ CatalogId ;

/* Variables and functions */
 TYPE_2__* extmembers ; 
 int numextmembers ; 
 int oidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ExtensionInfo *
findOwningExtension(CatalogId catalogId)
{
	ExtensionMemberId *low;
	ExtensionMemberId *high;

	/*
	 * We could use bsearch() here, but the notational cruft of calling
	 * bsearch is nearly as bad as doing it ourselves; and the generalized
	 * bsearch function is noticeably slower as well.
	 */
	if (numextmembers <= 0)
		return NULL;
	low = extmembers;
	high = extmembers + (numextmembers - 1);
	while (low <= high)
	{
		ExtensionMemberId *middle;
		int			difference;

		middle = low + (high - low) / 2;
		/* comparison must match ExtensionMemberIdCompare, below */
		difference = oidcmp(middle->catId.oid, catalogId.oid);
		if (difference == 0)
			difference = oidcmp(middle->catId.tableoid, catalogId.tableoid);
		if (difference == 0)
			return middle->ext;
		else if (difference < 0)
			low = middle + 1;
		else
			high = middle - 1;
	}
	return NULL;
}