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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 scalar_t__ MAX_BACKENDS ; 
 scalar_t__ MaxConnections ; 
 scalar_t__ autovacuum_max_workers ; 
 scalar_t__ max_worker_processes ; 

__attribute__((used)) static bool
check_max_wal_senders(int *newval, void **extra, GucSource source)
{
	if (MaxConnections + autovacuum_max_workers + 1 +
		max_worker_processes + *newval > MAX_BACKENDS)
		return false;
	return true;
}