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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ BPF_MAP_TYPE_LRU_PERCPU_HASH ; 
 scalar_t__ BPF_MAP_TYPE_PERCPU_ARRAY ; 
 scalar_t__ BPF_MAP_TYPE_PERCPU_HASH ; 

__attribute__((used)) static bool map_is_per_cpu(__u32 type)
{
	return type == BPF_MAP_TYPE_PERCPU_HASH ||
	       type == BPF_MAP_TYPE_PERCPU_ARRAY ||
	       type == BPF_MAP_TYPE_LRU_PERCPU_HASH;
}