#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rd_createSubid; scalar_t__ rd_newRelfilenodeSubid; } ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 scalar_t__ InvalidSubTransactionId ; 
 int /*<<< orphan*/  RelationClearRelation (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RelationDecrementReferenceCount (TYPE_1__*) ; 
 scalar_t__ RelationHasReferenceCountZero (TYPE_1__*) ; 

void
RelationClose(Relation relation)
{
	/* Note: no locking manipulations needed */
	RelationDecrementReferenceCount(relation);

#ifdef RELCACHE_FORCE_RELEASE
	if (RelationHasReferenceCountZero(relation) &&
		relation->rd_createSubid == InvalidSubTransactionId &&
		relation->rd_newRelfilenodeSubid == InvalidSubTransactionId)
		RelationClearRelation(relation, false);
#endif
}