#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cpus; } ;
struct TYPE_3__ {int aggr_mode; } ;

/* Variables and functions */
#define  AGGR_CORE 133 
#define  AGGR_GLOBAL 132 
#define  AGGR_NONE 131 
#define  AGGR_SOCKET 130 
#define  AGGR_THREAD 129 
#define  AGGR_UNSET 128 
 int ENOMEM ; 
 int /*<<< orphan*/  aggr_get_id ; 
 int /*<<< orphan*/  aggr_map ; 
 int /*<<< orphan*/  cpu_map__build_core_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_map__build_socket_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_map__empty_new (int) ; 
 int cpu_map__get_max (int /*<<< orphan*/ ) ; 
 scalar_t__ cpus_aggr_map ; 
 TYPE_2__* evsel_list ; 
 int /*<<< orphan*/  perf_stat__get_core_cached ; 
 int /*<<< orphan*/  perf_stat__get_socket_cached ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static int perf_stat_init_aggr_mode(void)
{
	int nr;

	switch (stat_config.aggr_mode) {
	case AGGR_SOCKET:
		if (cpu_map__build_socket_map(evsel_list->cpus, &aggr_map)) {
			perror("cannot build socket map");
			return -1;
		}
		aggr_get_id = perf_stat__get_socket_cached;
		break;
	case AGGR_CORE:
		if (cpu_map__build_core_map(evsel_list->cpus, &aggr_map)) {
			perror("cannot build core map");
			return -1;
		}
		aggr_get_id = perf_stat__get_core_cached;
		break;
	case AGGR_NONE:
	case AGGR_GLOBAL:
	case AGGR_THREAD:
	case AGGR_UNSET:
	default:
		break;
	}

	/*
	 * The evsel_list->cpus is the base we operate on,
	 * taking the highest cpu number to be the size of
	 * the aggregation translate cpumap.
	 */
	nr = cpu_map__get_max(evsel_list->cpus);
	cpus_aggr_map = cpu_map__empty_new(nr + 1);
	return cpus_aggr_map ? 0 : -ENOMEM;
}