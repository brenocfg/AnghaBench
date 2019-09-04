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
struct ring_buffer_per_cpu {int dummy; } ;
struct buffer_page {int dummy; } ;

/* Variables and functions */
 unsigned long RB_FLAG_MASK ; 
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,unsigned long) ; 

__attribute__((used)) static int rb_check_bpage(struct ring_buffer_per_cpu *cpu_buffer,
			  struct buffer_page *bpage)
{
	unsigned long val = (unsigned long)bpage;

	if (RB_WARN_ON(cpu_buffer, val & RB_FLAG_MASK))
		return 1;

	return 0;
}