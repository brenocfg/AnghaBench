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
struct cgroup {int options; int /*<<< orphan*/  memory; int /*<<< orphan*/  cpuacct_stat; int /*<<< orphan*/  io_serviced; int /*<<< orphan*/  io_service_bytes; int /*<<< orphan*/  io_queued; int /*<<< orphan*/  io_merged; int /*<<< orphan*/  throttle_io_serviced; int /*<<< orphan*/  throttle_io_service_bytes; int /*<<< orphan*/  cpuacct_usage; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CGROUP_OPTIONS_IS_UNIFIED ; 
 int /*<<< orphan*/  D_CGROUP ; 
 int /*<<< orphan*/  cgroup2_read_blkio (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cgroup2_read_cpuacct_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_read_blkio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_read_cpuacct_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_read_cpuacct_usage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_read_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cgroup_read(struct cgroup *cg) {
    debug(D_CGROUP, "reading metrics for cgroups '%s'", cg->id);
    if(!(cg->options & CGROUP_OPTIONS_IS_UNIFIED)) {
        cgroup_read_cpuacct_stat(&cg->cpuacct_stat);
        cgroup_read_cpuacct_usage(&cg->cpuacct_usage);
        cgroup_read_memory(&cg->memory, 0);
        cgroup_read_blkio(&cg->io_service_bytes);
        cgroup_read_blkio(&cg->io_serviced);
        cgroup_read_blkio(&cg->throttle_io_service_bytes);
        cgroup_read_blkio(&cg->throttle_io_serviced);
        cgroup_read_blkio(&cg->io_merged);
        cgroup_read_blkio(&cg->io_queued);
    }
    else {
        //TODO: io_service_bytes and io_serviced use same file merge into 1 function
        cgroup2_read_blkio(&cg->io_service_bytes, 0);
        cgroup2_read_blkio(&cg->io_serviced, 4);
        cgroup2_read_cpuacct_stat(&cg->cpuacct_stat);
        cgroup_read_memory(&cg->memory, 1);
    }
}