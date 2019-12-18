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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int rest_of_page (char*) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,char*,int) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 

__attribute__((used)) static int pack_sg_list(struct scatterlist *sg, int start,
			int limit, char *data, int count)
{
	int s;
	int index = start;

	while (count) {
		s = rest_of_page(data);
		if (s > count)
			s = count;
		BUG_ON(index >= limit);
		/* Make sure we don't terminate early. */
		sg_unmark_end(&sg[index]);
		sg_set_buf(&sg[index++], data, s);
		count -= s;
		data += s;
	}
	if (index-start)
		sg_mark_end(&sg[index - 1]);
	return index-start;
}