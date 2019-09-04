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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  offset_in_page (void*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,unsigned int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_addr_valid (void*) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

__attribute__((used)) static void
rpmsg_sg_init(struct scatterlist *sg, void *cpu_addr, unsigned int len)
{
	if (is_vmalloc_addr(cpu_addr)) {
		sg_init_table(sg, 1);
		sg_set_page(sg, vmalloc_to_page(cpu_addr), len,
			    offset_in_page(cpu_addr));
	} else {
		WARN_ON(!virt_addr_valid(cpu_addr));
		sg_init_one(sg, cpu_addr, len);
	}
}