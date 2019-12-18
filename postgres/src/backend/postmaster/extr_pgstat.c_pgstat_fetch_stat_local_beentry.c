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
typedef  int /*<<< orphan*/  LocalPgBackendStatus ;

/* Variables and functions */
 int /*<<< orphan*/ * localBackendStatusTable ; 
 int localNumBackends ; 
 int /*<<< orphan*/  pgstat_read_current_status () ; 

LocalPgBackendStatus *
pgstat_fetch_stat_local_beentry(int beid)
{
	pgstat_read_current_status();

	if (beid < 1 || beid > localNumBackends)
		return NULL;

	return &localBackendStatusTable[beid - 1];
}