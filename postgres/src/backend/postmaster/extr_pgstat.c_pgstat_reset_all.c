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
 int /*<<< orphan*/  PGSTAT_STAT_PERMANENT_DIRECTORY ; 
 int /*<<< orphan*/  pgstat_reset_remove_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_stat_directory ; 

void
pgstat_reset_all(void)
{
	pgstat_reset_remove_files(pgstat_stat_directory);
	pgstat_reset_remove_files(PGSTAT_STAT_PERMANENT_DIRECTORY);
}