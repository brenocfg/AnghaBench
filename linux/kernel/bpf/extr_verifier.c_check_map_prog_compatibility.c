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
struct bpf_verifier_env {int dummy; } ;
struct bpf_prog {scalar_t__ type; int /*<<< orphan*/  aux; } ;
struct bpf_map {struct bpf_map* inner_map_meta; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_PERF_EVENT ; 
 scalar_t__ BPF_PROG_TYPE_SOCKET_FILTER ; 
 int EINVAL ; 
 scalar_t__ bpf_map_is_dev_bound (struct bpf_map*) ; 
 int /*<<< orphan*/  bpf_offload_prog_map_match (struct bpf_prog*,struct bpf_map*) ; 
 scalar_t__ bpf_prog_is_dev_bound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_map_prealloc (struct bpf_map*) ; 
 scalar_t__ is_tracing_prog_type (scalar_t__) ; 
 scalar_t__ map_value_has_spin_lock (struct bpf_map*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static int check_map_prog_compatibility(struct bpf_verifier_env *env,
					struct bpf_map *map,
					struct bpf_prog *prog)

{
	/* Make sure that BPF_PROG_TYPE_PERF_EVENT programs only use
	 * preallocated hash maps, since doing memory allocation
	 * in overflow_handler can crash depending on where nmi got
	 * triggered.
	 */
	if (prog->type == BPF_PROG_TYPE_PERF_EVENT) {
		if (!check_map_prealloc(map)) {
			verbose(env, "perf_event programs can only use preallocated hash map\n");
			return -EINVAL;
		}
		if (map->inner_map_meta &&
		    !check_map_prealloc(map->inner_map_meta)) {
			verbose(env, "perf_event programs can only use preallocated inner hash map\n");
			return -EINVAL;
		}
	}

	if ((is_tracing_prog_type(prog->type) ||
	     prog->type == BPF_PROG_TYPE_SOCKET_FILTER) &&
	    map_value_has_spin_lock(map)) {
		verbose(env, "tracing progs cannot use bpf_spin_lock yet\n");
		return -EINVAL;
	}

	if ((bpf_prog_is_dev_bound(prog->aux) || bpf_map_is_dev_bound(map)) &&
	    !bpf_offload_prog_map_match(prog, map)) {
		verbose(env, "offload device mismatch between prog and map\n");
		return -EINVAL;
	}

	return 0;
}