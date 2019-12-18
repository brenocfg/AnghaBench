#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleHashEntryData ;
typedef  int Size ;
typedef  int /*<<< orphan*/  AggStatePerGroupData ;

/* Variables and functions */
 int MAXALIGN (int) ; 

Size
hash_agg_entry_size(int numAggs)
{
	Size		entrysize;

	/* This must match build_hash_table */
	entrysize = sizeof(TupleHashEntryData) +
		numAggs * sizeof(AggStatePerGroupData);
	entrysize = MAXALIGN(entrysize);

	return entrysize;
}