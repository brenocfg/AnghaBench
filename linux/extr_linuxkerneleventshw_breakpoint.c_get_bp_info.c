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
struct bp_cpuinfo {int dummy; } ;
typedef  enum bp_type_idx { ____Placeholder_bp_type_idx } bp_type_idx ;

/* Variables and functions */
 int bp_cpuinfo ; 
 struct bp_cpuinfo* per_cpu_ptr (int,int) ; 

__attribute__((used)) static struct bp_cpuinfo *get_bp_info(int cpu, enum bp_type_idx type)
{
	return per_cpu_ptr(bp_cpuinfo + type, cpu);
}