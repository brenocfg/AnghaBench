#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cpus; } ;
struct TYPE_6__ {TYPE_1__ core; } ;
struct TYPE_5__ {int aggr_mode; scalar_t__ cpus_aggr_map; void* aggr_get_id; int /*<<< orphan*/  aggr_map; } ;

/* Variables and functions */
#define  AGGR_CORE 134 
#define  AGGR_DIE 133 
#define  AGGR_GLOBAL 132 
#define  AGGR_NONE 131 
#define  AGGR_SOCKET 130 
#define  AGGR_THREAD 129 
#define  AGGR_UNSET 128 
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_map__build_core_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_map__build_die_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_map__build_socket_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* evsel_list ; 
 scalar_t__ perf_cpu_map__empty_new (int) ; 
 int perf_cpu_map__max (int /*<<< orphan*/ ) ; 
 void* perf_stat__get_core_cached ; 
 void* perf_stat__get_die_cached ; 
 void* perf_stat__get_socket_cached ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_2__ stat_config ; 
 int /*<<< orphan*/  term_percore_set () ; 

__attribute__((used)) static int perf_stat_init_aggr_mode(void)
{
	int nr;

	switch (stat_config.aggr_mode) {
	case AGGR_SOCKET:
		if (cpu_map__build_socket_map(evsel_list->core.cpus, &stat_config.aggr_map)) {
			perror("cannot build socket map");
			return -1;
		}
		stat_config.aggr_get_id = perf_stat__get_socket_cached;
		break;
	case AGGR_DIE:
		if (cpu_map__build_die_map(evsel_list->core.cpus, &stat_config.aggr_map)) {
			perror("cannot build die map");
			return -1;
		}
		stat_config.aggr_get_id = perf_stat__get_die_cached;
		break;
	case AGGR_CORE:
		if (cpu_map__build_core_map(evsel_list->core.cpus, &stat_config.aggr_map)) {
			perror("cannot build core map");
			return -1;
		}
		stat_config.aggr_get_id = perf_stat__get_core_cached;
		break;
	case AGGR_NONE:
		if (term_percore_set()) {
			if (cpu_map__build_core_map(evsel_list->core.cpus,
						    &stat_config.aggr_map)) {
				perror("cannot build core map");
				return -1;
			}
			stat_config.aggr_get_id = perf_stat__get_core_cached;
		}
		break;
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
	nr = perf_cpu_map__max(evsel_list->core.cpus);
	stat_config.cpus_aggr_map = perf_cpu_map__empty_new(nr + 1);
	return stat_config.cpus_aggr_map ? 0 : -ENOMEM;
}