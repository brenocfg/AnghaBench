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
struct map {int dummy; } ;
struct machine {struct map* vmlinux_map; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct map *machine__kernel_map(struct machine *machine)
{
	return machine->vmlinux_map;
}