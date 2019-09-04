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
struct target {scalar_t__ cpu_list; scalar_t__ system_wide; } ;

/* Variables and functions */

__attribute__((used)) static inline bool target__has_cpu(struct target *target)
{
	return target->system_wide || target->cpu_list;
}