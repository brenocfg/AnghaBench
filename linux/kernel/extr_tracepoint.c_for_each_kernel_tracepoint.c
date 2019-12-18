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

/* Variables and functions */
 int /*<<< orphan*/  __start___tracepoints_ptrs ; 
 int /*<<< orphan*/  __stop___tracepoints_ptrs ; 
 int /*<<< orphan*/  for_each_tracepoint_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct tracepoint*,void*),void*) ; 

void for_each_kernel_tracepoint(void (*fct)(struct tracepoint *tp, void *priv),
		void *priv)
{
	for_each_tracepoint_range(__start___tracepoints_ptrs,
		__stop___tracepoints_ptrs, fct, priv);
}