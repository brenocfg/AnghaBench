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
struct func_hook {scalar_t__ is_64bit_jump; } ;

/* Variables and functions */
 size_t JMP_32_SIZE ; 
 size_t JMP_64_SIZE ; 

__attribute__((used)) static inline size_t patch_size(struct func_hook *hook)
{
	return hook->is_64bit_jump ? JMP_64_SIZE : JMP_32_SIZE;
}