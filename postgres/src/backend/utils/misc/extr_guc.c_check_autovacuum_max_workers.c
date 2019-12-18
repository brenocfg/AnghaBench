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
 scalar_t__ max_wal_senders ; 
 scalar_t__ max_worker_processes ; 

__attribute__((used)) static bool
check_autovacuum_max_workers(int *newval, void **extra, GucSource source)
{
	if (MaxConnections + *newval + 1 +
		max_worker_processes + max_wal_senders > MAX_BACKENDS)
		return false;
	return true;
}