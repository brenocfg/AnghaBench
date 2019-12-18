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
struct TYPE_3__ {int /*<<< orphan*/  tableoid; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ catId; } ;
typedef  TYPE_2__ ExtensionMemberId ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ExtensionMemberIdCompare(const void *p1, const void *p2)
{
	const ExtensionMemberId *obj1 = (const ExtensionMemberId *) p1;
	const ExtensionMemberId *obj2 = (const ExtensionMemberId *) p2;
	int			cmpval;

	/*
	 * Compare OID first since it's usually unique, whereas there will only be
	 * a few distinct values of tableoid.
	 */
	cmpval = oidcmp(obj1->catId.oid, obj2->catId.oid);
	if (cmpval == 0)
		cmpval = oidcmp(obj1->catId.tableoid, obj2->catId.tableoid);
	return cmpval;
}