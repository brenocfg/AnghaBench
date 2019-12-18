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
struct TYPE_6__ {int hashso_buc_populated; int hashso_buc_split; scalar_t__ numKilled; int /*<<< orphan*/ * killedItems; void* hashso_split_bucket_buf; void* hashso_bucket_buf; int /*<<< orphan*/  currPos; } ;
struct TYPE_5__ {TYPE_2__* opaque; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  HashScanOpaqueData ;
typedef  TYPE_2__* HashScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HashScanPosInvalidate (int /*<<< orphan*/ ) ; 
 void* InvalidBuffer ; 
 TYPE_1__* RelationGetIndexScan (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ palloc (int) ; 

IndexScanDesc
hashbeginscan(Relation rel, int nkeys, int norderbys)
{
	IndexScanDesc scan;
	HashScanOpaque so;

	/* no order by operators allowed */
	Assert(norderbys == 0);

	scan = RelationGetIndexScan(rel, nkeys, norderbys);

	so = (HashScanOpaque) palloc(sizeof(HashScanOpaqueData));
	HashScanPosInvalidate(so->currPos);
	so->hashso_bucket_buf = InvalidBuffer;
	so->hashso_split_bucket_buf = InvalidBuffer;

	so->hashso_buc_populated = false;
	so->hashso_buc_split = false;

	so->killedItems = NULL;
	so->numKilled = 0;

	scan->opaque = so;

	return scan;
}