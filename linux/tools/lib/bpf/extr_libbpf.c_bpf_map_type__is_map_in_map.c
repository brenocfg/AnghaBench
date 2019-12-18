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
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;

/* Variables and functions */
 int BPF_MAP_TYPE_ARRAY_OF_MAPS ; 
 int BPF_MAP_TYPE_HASH_OF_MAPS ; 

__attribute__((used)) static bool bpf_map_type__is_map_in_map(enum bpf_map_type type)
{
	if (type == BPF_MAP_TYPE_ARRAY_OF_MAPS ||
	    type == BPF_MAP_TYPE_HASH_OF_MAPS)
		return true;
	return false;
}