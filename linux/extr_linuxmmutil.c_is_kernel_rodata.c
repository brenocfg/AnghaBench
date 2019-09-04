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
 scalar_t__ __end_rodata ; 
 scalar_t__ __start_rodata ; 

__attribute__((used)) static inline int is_kernel_rodata(unsigned long addr)
{
	return addr >= (unsigned long)__start_rodata &&
		addr < (unsigned long)__end_rodata;
}