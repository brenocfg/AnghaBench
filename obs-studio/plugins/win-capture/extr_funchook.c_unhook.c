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
struct func_hook {int hooked; scalar_t__ type; uintptr_t func_addr; void* rehook_data; void* unhook_data; } ;

/* Variables and functions */
 scalar_t__ HOOKTYPE_FORWARD_OVERWRITE ; 
 scalar_t__ HOOKTYPE_REVERSE_CHAIN ; 
 size_t JMP_32_SIZE ; 
 int /*<<< orphan*/  fix_permissions (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 size_t patch_size (struct func_hook*) ; 

void unhook(struct func_hook *hook)
{
	uintptr_t addr;
	size_t size;

	if (!hook->hooked)
		return;

	if (hook->type == HOOKTYPE_REVERSE_CHAIN) {
		size = JMP_32_SIZE;
		addr = (hook->func_addr - JMP_32_SIZE);
	} else {
		size = patch_size(hook);
		addr = hook->func_addr;
	}

	fix_permissions((void *)addr, size);
	memcpy(hook->rehook_data, (void *)addr, size);

	if (hook->type == HOOKTYPE_FORWARD_OVERWRITE)
		memcpy((void *)hook->func_addr, hook->unhook_data, size);

	hook->hooked = false;
}