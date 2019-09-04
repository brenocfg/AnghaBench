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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct func_hook {int hooked; scalar_t__ func_addr; scalar_t__ hook_addr; int /*<<< orphan*/  type; void* call_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOOKTYPE_REVERSE_CHAIN ; 
 int /*<<< orphan*/  X86_JMP_NEG_5 ; 

__attribute__((used)) static inline void hook_reverse_new(struct func_hook *hook, uint8_t *p)
{
	hook->call_addr = (void*)(hook->func_addr + 2);
	hook->type = HOOKTYPE_REVERSE_CHAIN;
	hook->hooked = true;

	p[0] = 0xE9;
	*((uint32_t*)&p[1]) = (uint32_t)(hook->hook_addr - hook->func_addr);
	*((uint16_t*)&p[5]) = X86_JMP_NEG_5;
}