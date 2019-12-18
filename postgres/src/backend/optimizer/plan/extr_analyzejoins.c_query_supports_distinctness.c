#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ distinctClause; scalar_t__ groupClause; scalar_t__ groupingSets; scalar_t__ setOperations; scalar_t__ havingQual; scalar_t__ hasAggs; scalar_t__ hasTargetSRFs; } ;
typedef  TYPE_1__ Query ;

/* Variables and functions */
 scalar_t__ NIL ; 

bool
query_supports_distinctness(Query *query)
{
	/* SRFs break distinctness except with DISTINCT, see below */
	if (query->hasTargetSRFs && query->distinctClause == NIL)
		return false;

	/* check for features we can prove distinctness with */
	if (query->distinctClause != NIL ||
		query->groupClause != NIL ||
		query->groupingSets != NIL ||
		query->hasAggs ||
		query->havingQual ||
		query->setOperations)
		return true;

	return false;
}