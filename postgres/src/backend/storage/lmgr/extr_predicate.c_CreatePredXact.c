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
struct TYPE_4__ {int /*<<< orphan*/  activeList; int /*<<< orphan*/  availableList; } ;
struct TYPE_3__ {int /*<<< orphan*/  sxact; int /*<<< orphan*/  link; } ;
typedef  int /*<<< orphan*/  SERIALIZABLEXACT ;
typedef  TYPE_1__* PredXactListElement ;

/* Variables and functions */
 TYPE_2__* PredXact ; 
 int /*<<< orphan*/  PredXactListElementData ; 
 int /*<<< orphan*/  SHMQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMQueueInsertBefore (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SHMQueueNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SERIALIZABLEXACT *
CreatePredXact(void)
{
	PredXactListElement ptle;

	ptle = (PredXactListElement)
		SHMQueueNext(&PredXact->availableList,
					 &PredXact->availableList,
					 offsetof(PredXactListElementData, link));
	if (!ptle)
		return NULL;

	SHMQueueDelete(&ptle->link);
	SHMQueueInsertBefore(&PredXact->activeList, &ptle->link);
	return &ptle->sxact;
}