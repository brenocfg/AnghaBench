#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatabaseNameIndexId ; 
 int RelationSupportsSysCache (scalar_t__) ; 
 scalar_t__ SharedSecLabelObjectIndexId ; 
 scalar_t__ SharedSecLabelRelationId ; 
 scalar_t__ TriggerRelidNameIndexId ; 

bool
RelationIdIsInInitFile(Oid relationId)
{
	if (relationId == SharedSecLabelRelationId ||
		relationId == TriggerRelidNameIndexId ||
		relationId == DatabaseNameIndexId ||
		relationId == SharedSecLabelObjectIndexId)
	{
		/*
		 * If this Assert fails, we don't need the applicable special case
		 * anymore.
		 */
		Assert(!RelationSupportsSysCache(relationId));
		return true;
	}
	return RelationSupportsSysCache(relationId);
}