#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* j_devname; int /*<<< orphan*/  j_proc_entry; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_jbd2_stats ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jbd2_stats_proc_exit(journal_t *journal)
{
	remove_proc_entry("info", journal->j_proc_entry);
	remove_proc_entry(journal->j_devname, proc_jbd2_stats);
}