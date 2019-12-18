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
typedef  int /*<<< orphan*/  u32 ;
struct globals {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_get_smp_processor_id () ; 
 struct globals* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_map ; 

__attribute__((used)) static struct globals *this_cpu_globals(void)
{
	u32 key = bpf_get_smp_processor_id();

	return bpf_map_lookup_elem(&percpu_map, &key);
}