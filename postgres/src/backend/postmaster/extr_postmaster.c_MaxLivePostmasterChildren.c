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
 int MaxConnections ; 
 int autovacuum_max_workers ; 
 int max_wal_senders ; 
 int max_worker_processes ; 

int
MaxLivePostmasterChildren(void)
{
	return 2 * (MaxConnections + autovacuum_max_workers + 1 +
				max_wal_senders + max_worker_processes);
}