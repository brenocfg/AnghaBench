#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stats_record {int /*<<< orphan*/  xdp_devmap_xmit; int /*<<< orphan*/  xdp_cpumap_kthread; int /*<<< orphan*/ * xdp_cpumap_enqueue; int /*<<< orphan*/ * xdp_exception; int /*<<< orphan*/ * xdp_redirect; } ;
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 int MAX_CPUS ; 
 int REDIR_RES_MAX ; 
 int XDP_ACTION_MAX ; 
 int /*<<< orphan*/  map_collect_record (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_collect_record_u64 (int,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* map_data ; 

__attribute__((used)) static bool stats_collect(struct stats_record *rec)
{
	int fd;
	int i;

	/* TODO: Detect if someone unloaded the perf event_fd's, as
	 * this can happen by someone running perf-record -e
	 */

	fd = map_data[0].fd; /* map0: redirect_err_cnt */
	for (i = 0; i < REDIR_RES_MAX; i++)
		map_collect_record_u64(fd, i, &rec->xdp_redirect[i]);

	fd = map_data[1].fd; /* map1: exception_cnt */
	for (i = 0; i < XDP_ACTION_MAX; i++) {
		map_collect_record_u64(fd, i, &rec->xdp_exception[i]);
	}

	fd = map_data[2].fd; /* map2: cpumap_enqueue_cnt */
	for (i = 0; i < MAX_CPUS; i++)
		map_collect_record(fd, i, &rec->xdp_cpumap_enqueue[i]);

	fd = map_data[3].fd; /* map3: cpumap_kthread_cnt */
	map_collect_record(fd, 0, &rec->xdp_cpumap_kthread);

	fd = map_data[4].fd; /* map4: devmap_xmit_cnt */
	map_collect_record(fd, 0, &rec->xdp_devmap_xmit);

	return true;
}