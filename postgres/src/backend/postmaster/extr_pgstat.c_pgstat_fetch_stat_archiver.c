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
typedef  int /*<<< orphan*/  PgStat_ArchiverStats ;

/* Variables and functions */
 int /*<<< orphan*/  archiverStats ; 
 int /*<<< orphan*/  backend_read_statsfile () ; 

PgStat_ArchiverStats *
pgstat_fetch_stat_archiver(void)
{
	backend_read_statsfile();

	return &archiverStats;
}