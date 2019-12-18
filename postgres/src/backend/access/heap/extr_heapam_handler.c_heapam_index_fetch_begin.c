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
struct TYPE_5__ {int /*<<< orphan*/  rel; } ;
struct TYPE_6__ {TYPE_1__ xs_base; int /*<<< orphan*/  xs_cbuf; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ IndexFetchTableData ;
typedef  TYPE_2__ IndexFetchHeapData ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBuffer ; 
 TYPE_2__* palloc0 (int) ; 

__attribute__((used)) static IndexFetchTableData *
heapam_index_fetch_begin(Relation rel)
{
	IndexFetchHeapData *hscan = palloc0(sizeof(IndexFetchHeapData));

	hscan->xs_base.rel = rel;
	hscan->xs_cbuf = InvalidBuffer;

	return &hscan->xs_base;
}