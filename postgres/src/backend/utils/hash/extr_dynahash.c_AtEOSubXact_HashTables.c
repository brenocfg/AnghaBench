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

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int num_seq_scans ; 
 int* seq_scan_level ; 
 int /*<<< orphan*/ * seq_scan_tables ; 

void
AtEOSubXact_HashTables(bool isCommit, int nestDepth)
{
	int			i;

	/*
	 * Search backward to make cleanup easy.  Note we must check all entries,
	 * not only those at the end of the array, because deletion technique
	 * doesn't keep them in order.
	 */
	for (i = num_seq_scans - 1; i >= 0; i--)
	{
		if (seq_scan_level[i] >= nestDepth)
		{
			if (isCommit)
				elog(WARNING, "leaked hash_seq_search scan for hash table %p",
					 seq_scan_tables[i]);
			seq_scan_tables[i] = seq_scan_tables[num_seq_scans - 1];
			seq_scan_level[i] = seq_scan_level[num_seq_scans - 1];
			num_seq_scans--;
		}
	}
}