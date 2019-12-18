#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int es_num_result_relations; TYPE_1__* es_result_relations; } ;
struct TYPE_4__ {scalar_t__ ri_RangeTableIndex; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  scalar_t__ Index ;
typedef  TYPE_2__ EState ;

/* Variables and functions */

bool
ExecRelationIsTargetRelation(EState *estate, Index scanrelid)
{
	ResultRelInfo *resultRelInfos;
	int			i;

	resultRelInfos = estate->es_result_relations;
	for (i = 0; i < estate->es_num_result_relations; i++)
	{
		if (resultRelInfos[i].ri_RangeTableIndex == scanrelid)
			return true;
	}
	return false;
}