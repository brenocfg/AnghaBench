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
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUACCT_STAT_NSTATS ; 
 int /*<<< orphan*/  __cpuusage_read (struct cgroup_subsys_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 cpuusage_read(struct cgroup_subsys_state *css, struct cftype *cft)
{
	return __cpuusage_read(css, CPUACCT_STAT_NSTATS);
}