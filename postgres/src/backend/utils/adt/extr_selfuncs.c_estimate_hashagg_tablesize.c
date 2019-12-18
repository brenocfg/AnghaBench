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
struct TYPE_8__ {int /*<<< orphan*/  numAggs; scalar_t__ transitionSpace; } ;
struct TYPE_7__ {TYPE_1__* pathtarget; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; } ;
typedef  double Size ;
typedef  TYPE_2__ Path ;
typedef  TYPE_3__ AggClauseCosts ;

/* Variables and functions */
 double MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeofMinimalTupleHeader ; 
 scalar_t__ hash_agg_entry_size (int /*<<< orphan*/ ) ; 

double
estimate_hashagg_tablesize(Path *path, const AggClauseCosts *agg_costs,
						   double dNumGroups)
{
	Size		hashentrysize;

	/* Estimate per-hash-entry space at tuple width... */
	hashentrysize = MAXALIGN(path->pathtarget->width) +
		MAXALIGN(SizeofMinimalTupleHeader);

	/* plus space for pass-by-ref transition values... */
	hashentrysize += agg_costs->transitionSpace;
	/* plus the per-hash-entry overhead */
	hashentrysize += hash_agg_entry_size(agg_costs->numAggs);

	/*
	 * Note that this disregards the effect of fill-factor and growth policy
	 * of the hash table.  That's probably ok, given that the default
	 * fill-factor is relatively high.  It'd be hard to meaningfully factor in
	 * "double-in-size" growth policies here.
	 */
	return hashentrysize * dNumGroups;
}