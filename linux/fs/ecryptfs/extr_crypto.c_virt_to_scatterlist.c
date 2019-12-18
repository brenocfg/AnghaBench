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
struct scatterlist {int length; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int offset_in_page (void const*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int /*<<< orphan*/ ,int) ; 
 struct page* virt_to_page (void const*) ; 

int virt_to_scatterlist(const void *addr, int size, struct scatterlist *sg,
			int sg_size)
{
	int i = 0;
	struct page *pg;
	int offset;
	int remainder_of_page;

	sg_init_table(sg, sg_size);

	while (size > 0 && i < sg_size) {
		pg = virt_to_page(addr);
		offset = offset_in_page(addr);
		sg_set_page(&sg[i], pg, 0, offset);
		remainder_of_page = PAGE_SIZE - offset;
		if (size >= remainder_of_page) {
			sg[i].length = remainder_of_page;
			addr += remainder_of_page;
			size -= remainder_of_page;
		} else {
			sg[i].length = size;
			addr += size;
			size = 0;
		}
		i++;
	}
	if (size > 0)
		return -ENOMEM;
	return i;
}