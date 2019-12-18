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
struct auto_mem {int /*<<< orphan*/  next; void* pointer; } ;

/* Variables and functions */
 scalar_t__ ecpg_alloc (int,int) ; 
 int /*<<< orphan*/  get_auto_allocs () ; 
 int /*<<< orphan*/  set_auto_allocs (struct auto_mem*) ; 

bool
ecpg_add_mem(void *ptr, int lineno)
{
	struct auto_mem *am = (struct auto_mem *) ecpg_alloc(sizeof(struct auto_mem), lineno);

	if (!am)
		return false;

	am->pointer = ptr;
	am->next = get_auto_allocs();
	set_auto_allocs(am);
	return true;
}