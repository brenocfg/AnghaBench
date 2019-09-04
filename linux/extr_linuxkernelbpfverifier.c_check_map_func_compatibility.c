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
struct bpf_verifier_env {int subprog_cnt; } ;
struct bpf_map {int map_type; } ;

/* Variables and functions */
#define  BPF_FUNC_current_task_under_cgroup 156 
#define  BPF_FUNC_get_local_storage 155 
#define  BPF_FUNC_get_stackid 154 
 int BPF_FUNC_map_delete_elem ; 
 int BPF_FUNC_map_lookup_elem ; 
#define  BPF_FUNC_msg_redirect_hash 153 
#define  BPF_FUNC_msg_redirect_map 152 
#define  BPF_FUNC_perf_event_output 151 
#define  BPF_FUNC_perf_event_read 150 
#define  BPF_FUNC_perf_event_read_value 149 
#define  BPF_FUNC_redirect_map 148 
#define  BPF_FUNC_sk_redirect_hash 147 
#define  BPF_FUNC_sk_redirect_map 146 
#define  BPF_FUNC_sk_select_reuseport 145 
#define  BPF_FUNC_skb_under_cgroup 144 
#define  BPF_FUNC_sock_hash_update 143 
#define  BPF_FUNC_sock_map_update 142 
#define  BPF_FUNC_tail_call 141 
#define  BPF_MAP_TYPE_ARRAY_OF_MAPS 140 
#define  BPF_MAP_TYPE_CGROUP_ARRAY 139 
#define  BPF_MAP_TYPE_CGROUP_STORAGE 138 
#define  BPF_MAP_TYPE_CPUMAP 137 
#define  BPF_MAP_TYPE_DEVMAP 136 
#define  BPF_MAP_TYPE_HASH_OF_MAPS 135 
#define  BPF_MAP_TYPE_PERF_EVENT_ARRAY 134 
#define  BPF_MAP_TYPE_PROG_ARRAY 133 
#define  BPF_MAP_TYPE_REUSEPORT_SOCKARRAY 132 
#define  BPF_MAP_TYPE_SOCKHASH 131 
#define  BPF_MAP_TYPE_SOCKMAP 130 
#define  BPF_MAP_TYPE_STACK_TRACE 129 
#define  BPF_MAP_TYPE_XSKMAP 128 
 int EINVAL ; 
 int /*<<< orphan*/  func_id_name (int) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_map_func_compatibility(struct bpf_verifier_env *env,
					struct bpf_map *map, int func_id)
{
	if (!map)
		return 0;

	/* We need a two way check, first is from map perspective ... */
	switch (map->map_type) {
	case BPF_MAP_TYPE_PROG_ARRAY:
		if (func_id != BPF_FUNC_tail_call)
			goto error;
		break;
	case BPF_MAP_TYPE_PERF_EVENT_ARRAY:
		if (func_id != BPF_FUNC_perf_event_read &&
		    func_id != BPF_FUNC_perf_event_output &&
		    func_id != BPF_FUNC_perf_event_read_value)
			goto error;
		break;
	case BPF_MAP_TYPE_STACK_TRACE:
		if (func_id != BPF_FUNC_get_stackid)
			goto error;
		break;
	case BPF_MAP_TYPE_CGROUP_ARRAY:
		if (func_id != BPF_FUNC_skb_under_cgroup &&
		    func_id != BPF_FUNC_current_task_under_cgroup)
			goto error;
		break;
	case BPF_MAP_TYPE_CGROUP_STORAGE:
		if (func_id != BPF_FUNC_get_local_storage)
			goto error;
		break;
	/* devmap returns a pointer to a live net_device ifindex that we cannot
	 * allow to be modified from bpf side. So do not allow lookup elements
	 * for now.
	 */
	case BPF_MAP_TYPE_DEVMAP:
		if (func_id != BPF_FUNC_redirect_map)
			goto error;
		break;
	/* Restrict bpf side of cpumap and xskmap, open when use-cases
	 * appear.
	 */
	case BPF_MAP_TYPE_CPUMAP:
	case BPF_MAP_TYPE_XSKMAP:
		if (func_id != BPF_FUNC_redirect_map)
			goto error;
		break;
	case BPF_MAP_TYPE_ARRAY_OF_MAPS:
	case BPF_MAP_TYPE_HASH_OF_MAPS:
		if (func_id != BPF_FUNC_map_lookup_elem)
			goto error;
		break;
	case BPF_MAP_TYPE_SOCKMAP:
		if (func_id != BPF_FUNC_sk_redirect_map &&
		    func_id != BPF_FUNC_sock_map_update &&
		    func_id != BPF_FUNC_map_delete_elem &&
		    func_id != BPF_FUNC_msg_redirect_map)
			goto error;
		break;
	case BPF_MAP_TYPE_SOCKHASH:
		if (func_id != BPF_FUNC_sk_redirect_hash &&
		    func_id != BPF_FUNC_sock_hash_update &&
		    func_id != BPF_FUNC_map_delete_elem &&
		    func_id != BPF_FUNC_msg_redirect_hash)
			goto error;
		break;
	case BPF_MAP_TYPE_REUSEPORT_SOCKARRAY:
		if (func_id != BPF_FUNC_sk_select_reuseport)
			goto error;
		break;
	default:
		break;
	}

	/* ... and second from the function itself. */
	switch (func_id) {
	case BPF_FUNC_tail_call:
		if (map->map_type != BPF_MAP_TYPE_PROG_ARRAY)
			goto error;
		if (env->subprog_cnt > 1) {
			verbose(env, "tail_calls are not allowed in programs with bpf-to-bpf calls\n");
			return -EINVAL;
		}
		break;
	case BPF_FUNC_perf_event_read:
	case BPF_FUNC_perf_event_output:
	case BPF_FUNC_perf_event_read_value:
		if (map->map_type != BPF_MAP_TYPE_PERF_EVENT_ARRAY)
			goto error;
		break;
	case BPF_FUNC_get_stackid:
		if (map->map_type != BPF_MAP_TYPE_STACK_TRACE)
			goto error;
		break;
	case BPF_FUNC_current_task_under_cgroup:
	case BPF_FUNC_skb_under_cgroup:
		if (map->map_type != BPF_MAP_TYPE_CGROUP_ARRAY)
			goto error;
		break;
	case BPF_FUNC_redirect_map:
		if (map->map_type != BPF_MAP_TYPE_DEVMAP &&
		    map->map_type != BPF_MAP_TYPE_CPUMAP &&
		    map->map_type != BPF_MAP_TYPE_XSKMAP)
			goto error;
		break;
	case BPF_FUNC_sk_redirect_map:
	case BPF_FUNC_msg_redirect_map:
	case BPF_FUNC_sock_map_update:
		if (map->map_type != BPF_MAP_TYPE_SOCKMAP)
			goto error;
		break;
	case BPF_FUNC_sk_redirect_hash:
	case BPF_FUNC_msg_redirect_hash:
	case BPF_FUNC_sock_hash_update:
		if (map->map_type != BPF_MAP_TYPE_SOCKHASH)
			goto error;
		break;
	case BPF_FUNC_get_local_storage:
		if (map->map_type != BPF_MAP_TYPE_CGROUP_STORAGE)
			goto error;
		break;
	case BPF_FUNC_sk_select_reuseport:
		if (map->map_type != BPF_MAP_TYPE_REUSEPORT_SOCKARRAY)
			goto error;
		break;
	default:
		break;
	}

	return 0;
error:
	verbose(env, "cannot pass map_type %d into func %s#%d\n",
		map->map_type, func_id_name(func_id), func_id);
	return -EINVAL;
}