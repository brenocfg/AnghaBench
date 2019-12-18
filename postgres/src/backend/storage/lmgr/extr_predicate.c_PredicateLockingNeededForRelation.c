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
struct TYPE_6__ {scalar_t__ rd_id; TYPE_1__* rd_rel; } ;
struct TYPE_5__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 scalar_t__ FirstBootstrapObjectId ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RelationUsesLocalBuffers (TYPE_2__*) ; 

__attribute__((used)) static inline bool
PredicateLockingNeededForRelation(Relation relation)
{
	return !(relation->rd_id < FirstBootstrapObjectId ||
			 RelationUsesLocalBuffers(relation) ||
			 relation->rd_rel->relkind == RELKIND_MATVIEW);
}