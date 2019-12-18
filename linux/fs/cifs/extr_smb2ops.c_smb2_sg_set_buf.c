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
 scalar_t__ is_vmalloc_addr (void const*) ; 
 int /*<<< orphan*/  offset_in_page (void const*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 void* virt_to_page (void const*) ; 
 void* vmalloc_to_page (void const*) ; 

__attribute__((used)) static inline void smb2_sg_set_buf(struct scatterlist *sg, const void *buf,
				   unsigned int buflen)
{
	void *addr;
	/*
	 * VMAP_STACK (at least) puts stack into the vmalloc address space
	 */
	if (is_vmalloc_addr(buf))
		addr = vmalloc_to_page(buf);
	else
		addr = virt_to_page(buf);
	sg_set_page(sg, addr, buflen, offset_in_page(buf));
}