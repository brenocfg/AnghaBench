#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ numKilled; int hashso_buc_populated; int hashso_buc_split; int /*<<< orphan*/  currPos; } ;
struct TYPE_6__ {int numberOfKeys; int /*<<< orphan*/  keyData; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  scalar_t__ ScanKey ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* HashScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  HashScanPosInvalidate (int /*<<< orphan*/ ) ; 
 scalar_t__ HashScanPosIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_dropscanbuf (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  _hash_kill_items (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
hashrescan(IndexScanDesc scan, ScanKey scankey, int nscankeys,
		   ScanKey orderbys, int norderbys)
{
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	Relation	rel = scan->indexRelation;

	if (HashScanPosIsValid(so->currPos))
	{
		/* Before leaving current page, deal with any killed items */
		if (so->numKilled > 0)
			_hash_kill_items(scan);
	}

	_hash_dropscanbuf(rel, so);

	/* set position invalid (this will cause _hash_first call) */
	HashScanPosInvalidate(so->currPos);

	/* Update scan key, if a new one is given */
	if (scankey && scan->numberOfKeys > 0)
	{
		memmove(scan->keyData,
				scankey,
				scan->numberOfKeys * sizeof(ScanKeyData));
	}

	so->hashso_buc_populated = false;
	so->hashso_buc_split = false;
}