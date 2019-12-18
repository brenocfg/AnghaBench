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
struct tracing_map_elt {int* var_set; } ;

/* Variables and functions */

bool tracing_map_var_set(struct tracing_map_elt *elt, unsigned int i)
{
	return elt->var_set[i];
}