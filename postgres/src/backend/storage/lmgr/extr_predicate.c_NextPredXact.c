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
struct TYPE_4__ {int /*<<< orphan*/  activeList; } ;
struct TYPE_3__ {int /*<<< orphan*/  sxact; int /*<<< orphan*/  link; } ;
typedef  int /*<<< orphan*/  SERIALIZABLEXACT ;
typedef  TYPE_1__* PredXactListElement ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* PredXact ; 
 int /*<<< orphan*/  PredXactListElementData ; 
 scalar_t__ SHMQueueNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ShmemAddrIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * link ; 
 char* offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SERIALIZABLEXACT *
NextPredXact(SERIALIZABLEXACT *sxact)
{
	PredXactListElement ptle;

	Assert(ShmemAddrIsValid(sxact));

	ptle = (PredXactListElement)
		(((char *) sxact)
		 - offsetof(PredXactListElementData, sxact)
		 + offsetof(PredXactListElementData, link));
	ptle = (PredXactListElement)
		SHMQueueNext(&PredXact->activeList,
					 &ptle->link,
					 offsetof(PredXactListElementData, link));
	if (!ptle)
		return NULL;

	return &ptle->sxact;
}