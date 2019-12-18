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
struct TYPE_6__ {int /*<<< orphan*/  ginstate; void* keyCtx; void* tempCtx; scalar_t__ nkeys; int /*<<< orphan*/ * keys; } ;
struct TYPE_5__ {TYPE_2__* opaque; int /*<<< orphan*/  indexRelation; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  GinScanOpaqueData ;
typedef  TYPE_2__* GinScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 void* AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 TYPE_1__* RelationGetIndexScan (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  initGinState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

IndexScanDesc
ginbeginscan(Relation rel, int nkeys, int norderbys)
{
	IndexScanDesc scan;
	GinScanOpaque so;

	/* no order by operators allowed */
	Assert(norderbys == 0);

	scan = RelationGetIndexScan(rel, nkeys, norderbys);

	/* allocate private workspace */
	so = (GinScanOpaque) palloc(sizeof(GinScanOpaqueData));
	so->keys = NULL;
	so->nkeys = 0;
	so->tempCtx = AllocSetContextCreate(CurrentMemoryContext,
										"Gin scan temporary context",
										ALLOCSET_DEFAULT_SIZES);
	so->keyCtx = AllocSetContextCreate(CurrentMemoryContext,
									   "Gin scan key context",
									   ALLOCSET_DEFAULT_SIZES);
	initGinState(&so->ginstate, scan->indexRelation);

	scan->opaque = so;

	return scan;
}