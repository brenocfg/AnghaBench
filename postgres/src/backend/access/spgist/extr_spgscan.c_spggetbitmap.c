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
typedef  scalar_t__ int64 ;
struct TYPE_6__ {int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
struct TYPE_5__ {int want_itup; scalar_t__ ntids; int /*<<< orphan*/ * tbm; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  TYPE_1__* SpGistScanOpaque ;
typedef  TYPE_2__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  spgWalk (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storeBitmap ; 

int64
spggetbitmap(IndexScanDesc scan, TIDBitmap *tbm)
{
	SpGistScanOpaque so = (SpGistScanOpaque) scan->opaque;

	/* Copy want_itup to *so so we don't need to pass it around separately */
	so->want_itup = false;

	so->tbm = tbm;
	so->ntids = 0;

	spgWalk(scan->indexRelation, so, true, storeBitmap, scan->xs_snapshot);

	return so->ntids;
}