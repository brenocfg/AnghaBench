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
struct TYPE_8__ {TYPE_2__* indexRelation; } ;
struct TYPE_7__ {TYPE_1__* rd_indam; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ammarkpos ) (TYPE_3__*) ;} ;
typedef  TYPE_3__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SCAN_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CHECKS ; 
 int /*<<< orphan*/  ammarkpos ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void
index_markpos(IndexScanDesc scan)
{
	SCAN_CHECKS;
	CHECK_SCAN_PROCEDURE(ammarkpos);

	scan->indexRelation->rd_indam->ammarkpos(scan);
}