#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* index; } ;
struct TYPE_7__ {TYPE_1__* rd_indam; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* ambulkdelete ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REL_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELATION_CHECKS ; 
 int /*<<< orphan*/  ambulkdelete ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

IndexBulkDeleteResult *
index_bulk_delete(IndexVacuumInfo *info,
				  IndexBulkDeleteResult *stats,
				  IndexBulkDeleteCallback callback,
				  void *callback_state)
{
	Relation	indexRelation = info->index;

	RELATION_CHECKS;
	CHECK_REL_PROCEDURE(ambulkdelete);

	return indexRelation->rd_indam->ambulkdelete(info, stats,
												 callback, callback_state);
}