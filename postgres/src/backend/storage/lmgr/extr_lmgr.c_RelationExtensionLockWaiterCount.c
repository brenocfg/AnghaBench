#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  relId; int /*<<< orphan*/  dbId; } ;
struct TYPE_6__ {TYPE_1__ lockRelId; } ;
struct TYPE_7__ {TYPE_2__ rd_lockInfo; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int LockWaiterCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_LOCKTAG_RELATION_EXTEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
RelationExtensionLockWaiterCount(Relation relation)
{
	LOCKTAG		tag;

	SET_LOCKTAG_RELATION_EXTEND(tag,
								relation->rd_lockInfo.lockRelId.dbId,
								relation->rd_lockInfo.lockRelId.relId);

	return LockWaiterCount(&tag);
}