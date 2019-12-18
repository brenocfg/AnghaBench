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
typedef  int /*<<< orphan*/  u64 ;
struct sysinfo {scalar_t__ procs; void** loads; int /*<<< orphan*/  uptime; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 void** avenrun ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_mono_fast_ns () ; 
 int /*<<< orphan*/  memset (struct sysinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nr_threads ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 

__attribute__((used)) static void kdb_sysinfo(struct sysinfo *val)
{
	u64 uptime = ktime_get_mono_fast_ns();

	memset(val, 0, sizeof(*val));
	val->uptime = div_u64(uptime, NSEC_PER_SEC);
	val->loads[0] = avenrun[0];
	val->loads[1] = avenrun[1];
	val->loads[2] = avenrun[2];
	val->procs = nr_threads-1;
	si_meminfo(val);

	return;
}