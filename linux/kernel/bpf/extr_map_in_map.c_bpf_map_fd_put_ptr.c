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
 int /*<<< orphan*/  bpf_map_put (void*) ; 

void bpf_map_fd_put_ptr(void *ptr)
{
	/* ptr->ops->map_free() has to go through one
	 * rcu grace period by itself.
	 */
	bpf_map_put(ptr);
}