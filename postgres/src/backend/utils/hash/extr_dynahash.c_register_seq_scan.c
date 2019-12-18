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
 int /*<<< orphan*/  GetCurrentTransactionNestLevel () ; 
 size_t MAX_SEQ_SCANS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t num_seq_scans ; 
 int /*<<< orphan*/ * seq_scan_level ; 
 TYPE_1__** seq_scan_tables ; 

__attribute__((used)) static void
register_seq_scan(HTAB *hashp)
{
	if (num_seq_scans >= MAX_SEQ_SCANS)
		elog(ERROR, "too many active hash_seq_search scans, cannot start one on \"%s\"",
			 hashp->tabname);
	seq_scan_tables[num_seq_scans] = hashp;
	seq_scan_level[num_seq_scans] = GetCurrentTransactionNestLevel();
	num_seq_scans++;
}