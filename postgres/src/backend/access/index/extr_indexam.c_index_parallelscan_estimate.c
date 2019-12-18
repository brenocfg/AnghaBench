#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* rd_indam; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* amestimateparallelscan ) () ;} ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  EstimateSnapshotSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParallelIndexScanDescData ; 
 int /*<<< orphan*/  RELATION_CHECKS ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_snapshot_data ; 
 int /*<<< orphan*/  stub1 () ; 

Size
index_parallelscan_estimate(Relation indexRelation, Snapshot snapshot)
{
	Size		nbytes;

	RELATION_CHECKS;

	nbytes = offsetof(ParallelIndexScanDescData, ps_snapshot_data);
	nbytes = add_size(nbytes, EstimateSnapshotSpace(snapshot));
	nbytes = MAXALIGN(nbytes);

	/*
	 * If amestimateparallelscan is not provided, assume there is no
	 * AM-specific data needed.  (It's hard to believe that could work, but
	 * it's easy enough to cater to it here.)
	 */
	if (indexRelation->rd_indam->amestimateparallelscan != NULL)
		nbytes = add_size(nbytes,
						  indexRelation->rd_indam->amestimateparallelscan());

	return nbytes;
}