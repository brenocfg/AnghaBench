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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 

__attribute__((used)) static int
pack_sg_list_p(struct scatterlist *sg, int start, int limit,
	       struct page **pdata, int nr_pages, size_t offs, int count)
{
	int i = 0, s;
	int data_off = offs;
	int index = start;

	BUG_ON(nr_pages > (limit - start));
	/*
	 * if the first page doesn't start at
	 * page boundary find the offset
	 */
	while (nr_pages) {
		s = PAGE_SIZE - data_off;
		if (s > count)
			s = count;
		BUG_ON(index >= limit);
		/* Make sure we don't terminate early. */
		sg_unmark_end(&sg[index]);
		sg_set_page(&sg[index++], pdata[i++], s, data_off);
		data_off = 0;
		count -= s;
		nr_pages--;
	}

	if (index-start)
		sg_mark_end(&sg[index - 1]);
	return index - start;
}