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

/* Variables and functions */
 int /*<<< orphan*/  __map__is_bpf_prog (struct map const*) ; 
 int /*<<< orphan*/  __map__is_extra_kernel_map (struct map const*) ; 
 int /*<<< orphan*/  __map__is_kernel (struct map const*) ; 

__attribute__((used)) static inline bool __map__is_kmodule(const struct map *map)
{
	return !__map__is_kernel(map) && !__map__is_extra_kernel_map(map) &&
	       !__map__is_bpf_prog(map);
}