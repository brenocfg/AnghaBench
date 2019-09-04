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
struct mem_section {int dummy; } ;

/* Variables and functions */
 int* mem_section ; 

int __section_nr(struct mem_section* ms)
{
	return (int)(ms - mem_section[0]);
}