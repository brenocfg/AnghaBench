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
typedef  int /*<<< orphan*/  uint8_t ;
struct func_hook {int hooked; int /*<<< orphan*/  type; scalar_t__ func_addr; void* call_addr; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOOKTYPE_FORWARD_OVERWRITE ; 

__attribute__((used)) static inline void hook_forward_overwrite(struct func_hook *hook,
		intptr_t offset)
{
	uint8_t *ptr = (uint8_t*)hook->func_addr;

	hook->call_addr = (void*)hook->func_addr;
	hook->type = HOOKTYPE_FORWARD_OVERWRITE;
	hook->hooked = true;

	*(ptr++) = 0xE9;
	*((int32_t*)ptr) = (int32_t)offset;
}