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
struct bpf_map_info {int /*<<< orphan*/  value_size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned int get_possible_cpus () ; 
 int /*<<< orphan*/  map_is_per_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 unsigned int round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_per_cpu_value(struct bpf_map_info *info, void *value)
{
	unsigned int i, n, step;

	if (!map_is_per_cpu(info->type))
		return;

	n = get_possible_cpus();
	step = round_up(info->value_size, 8);
	for (i = 1; i < n; i++)
		memcpy(value + i * step, value, info->value_size);
}