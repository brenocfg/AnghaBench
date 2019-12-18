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
struct bpf_map_def {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_TYPE_LRU_PERCPU_HASH ; 
 scalar_t__ BPF_MAP_TYPE_PERCPU_ARRAY ; 
 scalar_t__ BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE ; 
 scalar_t__ BPF_MAP_TYPE_PERCPU_HASH ; 

__attribute__((used)) static bool bpf_map_def__is_per_cpu(const struct bpf_map_def *def)
{
	return def->type == BPF_MAP_TYPE_PERCPU_HASH ||
	       def->type == BPF_MAP_TYPE_PERCPU_ARRAY ||
	       def->type == BPF_MAP_TYPE_LRU_PERCPU_HASH ||
	       def->type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE;
}