#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  availableList; } ;
struct TYPE_4__ {int /*<<< orphan*/  outLink; int /*<<< orphan*/  inLink; } ;
typedef  TYPE_1__* RWConflict ;

/* Variables and functions */
 TYPE_3__* RWConflictPool ; 
 int /*<<< orphan*/  SHMQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMQueueInsertBefore (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ReleaseRWConflict(RWConflict conflict)
{
	SHMQueueDelete(&conflict->inLink);
	SHMQueueDelete(&conflict->outLink);
	SHMQueueInsertBefore(&RWConflictPool->availableList, &conflict->outLink);
}