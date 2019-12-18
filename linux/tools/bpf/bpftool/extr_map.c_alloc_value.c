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
struct bpf_map_info {int value_size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int get_possible_cpus () ; 
 void* malloc (int) ; 
 scalar_t__ map_is_per_cpu (int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 

__attribute__((used)) static void *alloc_value(struct bpf_map_info *info)
{
	if (map_is_per_cpu(info->type))
		return malloc(round_up(info->value_size, 8) *
			      get_possible_cpus());
	else
		return malloc(info->value_size);
}