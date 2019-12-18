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
struct TYPE_4__ {int rd_refcnt; } ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeRelationRefs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberRelationRef (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
RelationIncrementReferenceCount(Relation rel)
{
	ResourceOwnerEnlargeRelationRefs(CurrentResourceOwner);
	rel->rd_refcnt += 1;
	if (!IsBootstrapProcessingMode())
		ResourceOwnerRememberRelationRef(CurrentResourceOwner, rel);
}