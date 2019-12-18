#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct perf_stat {TYPE_3__* session; } ;
struct perf_env {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpus; } ;
struct TYPE_10__ {TYPE_1__ core; } ;
struct TYPE_9__ {int aggr_mode; int /*<<< orphan*/  aggr_get_id; int /*<<< orphan*/  aggr_map; } ;
struct TYPE_7__ {struct perf_env env; } ;
struct TYPE_8__ {TYPE_2__ header; } ;

/* Variables and functions */
#define  AGGR_CORE 134 
#define  AGGR_DIE 133 
#define  AGGR_GLOBAL 132 
#define  AGGR_NONE 131 
#define  AGGR_SOCKET 130 
#define  AGGR_THREAD 129 
#define  AGGR_UNSET 128 
 TYPE_5__* evsel_list ; 
 int /*<<< orphan*/  perf_env__build_core_map (struct perf_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_env__build_die_map (struct perf_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_env__build_socket_map (struct perf_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_stat__get_core_file ; 
 int /*<<< orphan*/  perf_stat__get_die_file ; 
 int /*<<< orphan*/  perf_stat__get_socket_file ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_4__ stat_config ; 

__attribute__((used)) static int perf_stat_init_aggr_mode_file(struct perf_stat *st)
{
	struct perf_env *env = &st->session->header.env;

	switch (stat_config.aggr_mode) {
	case AGGR_SOCKET:
		if (perf_env__build_socket_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) {
			perror("cannot build socket map");
			return -1;
		}
		stat_config.aggr_get_id = perf_stat__get_socket_file;
		break;
	case AGGR_DIE:
		if (perf_env__build_die_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) {
			perror("cannot build die map");
			return -1;
		}
		stat_config.aggr_get_id = perf_stat__get_die_file;
		break;
	case AGGR_CORE:
		if (perf_env__build_core_map(env, evsel_list->core.cpus, &stat_config.aggr_map)) {
			perror("cannot build core map");
			return -1;
		}
		stat_config.aggr_get_id = perf_stat__get_core_file;
		break;
	case AGGR_NONE:
	case AGGR_GLOBAL:
	case AGGR_THREAD:
	case AGGR_UNSET:
	default:
		break;
	}

	return 0;
}