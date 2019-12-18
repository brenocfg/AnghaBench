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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ kasan_mem_to_shadow (void const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void print_tags(u8 addr_tag, const void *addr)
{
	u8 *shadow = (u8 *)kasan_mem_to_shadow(addr);

	pr_err("Pointer tag: [%02x], memory tag: [%02x]\n", addr_tag, *shadow);
}