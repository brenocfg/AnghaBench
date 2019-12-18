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
struct TYPE_4__ {int ispartition; int numParents; struct TYPE_4__** parents; } ;
typedef  TYPE_1__ TableInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static TableInfo *
getRootTableInfo(TableInfo *tbinfo)
{
	TableInfo  *parentTbinfo;

	Assert(tbinfo->ispartition);
	Assert(tbinfo->numParents == 1);

	parentTbinfo = tbinfo->parents[0];
	while (parentTbinfo->ispartition)
	{
		Assert(parentTbinfo->numParents == 1);
		parentTbinfo = parentTbinfo->parents[0];
	}

	return parentTbinfo;
}