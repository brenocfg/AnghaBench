#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ numKilled; struct TYPE_8__* killedItems; int /*<<< orphan*/  currPos; } ;
struct TYPE_7__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/  indexRelation; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* HashScanOpaque ;

/* Variables and functions */
 scalar_t__ HashScanPosIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_dropscanbuf (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  _hash_kill_items (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

void
hashendscan(IndexScanDesc scan)
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

	if (so->killedItems != NULL)
		pfree(so->killedItems);
	pfree(so);
	scan->opaque = NULL;
}