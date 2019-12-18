#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tabname; } ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int num_seq_scans ; 
 int /*<<< orphan*/ * seq_scan_level ; 
 TYPE_1__** seq_scan_tables ; 

__attribute__((used)) static void
deregister_seq_scan(HTAB *hashp)
{
	int			i;

	/* Search backward since it's most likely at the stack top */
	for (i = num_seq_scans - 1; i >= 0; i--)
	{
		if (seq_scan_tables[i] == hashp)
		{
			seq_scan_tables[i] = seq_scan_tables[num_seq_scans - 1];
			seq_scan_level[i] = seq_scan_level[num_seq_scans - 1];
			num_seq_scans--;
			return;
		}
	}
	elog(ERROR, "no hash_seq_search scan for hash table \"%s\"",
		 hashp->tabname);
}