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
struct func_map {scalar_t__ addr; } ;

/* Variables and functions */

__attribute__((used)) static int func_bcmp(const void *a, const void *b)
{
	const struct func_map *fa = a;
	const struct func_map *fb = b;

	if ((fa->addr == fb->addr) ||

	    (fa->addr > fb->addr &&
	     fa->addr < (fb+1)->addr))
		return 0;

	if (fa->addr < fb->addr)
		return -1;

	return 1;
}