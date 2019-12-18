#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  xs_cbuf; } ;
typedef  int /*<<< orphan*/  IndexFetchTableData ;
typedef  TYPE_1__ IndexFetchHeapData ;

/* Variables and functions */
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
heapam_index_fetch_reset(IndexFetchTableData *scan)
{
	IndexFetchHeapData *hscan = (IndexFetchHeapData *) scan;

	if (BufferIsValid(hscan->xs_cbuf))
	{
		ReleaseBuffer(hscan->xs_cbuf);
		hscan->xs_cbuf = InvalidBuffer;
	}
}