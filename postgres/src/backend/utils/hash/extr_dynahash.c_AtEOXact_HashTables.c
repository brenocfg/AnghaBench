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
 int /*<<< orphan*/ * seq_scan_tables ; 

void
AtEOXact_HashTables(bool isCommit)
{
	/*
	 * During abort cleanup, open scans are expected; just silently clean 'em
	 * out.  An open scan at commit means someone forgot a hash_seq_term()
	 * call, so complain.
	 *
	 * Note: it's tempting to try to print the tabname here, but refrain for
	 * fear of touching deallocated memory.  This isn't a user-facing message
	 * anyway, so it needn't be pretty.
	 */
	if (isCommit)
	{
		int			i;

		for (i = 0; i < num_seq_scans; i++)
		{
			elog(WARNING, "leaked hash_seq_search scan for hash table %p",
				 seq_scan_tables[i]);
		}
	}
	num_seq_scans = 0;
}