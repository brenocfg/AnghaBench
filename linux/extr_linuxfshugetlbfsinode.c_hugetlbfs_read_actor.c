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
struct page {int dummy; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 size_t copy_page_to_iter (struct page*,unsigned long,int,struct iov_iter*) ; 

__attribute__((used)) static size_t
hugetlbfs_read_actor(struct page *page, unsigned long offset,
			struct iov_iter *to, unsigned long size)
{
	size_t copied = 0;
	int i, chunksize;

	/* Find which 4k chunk and offset with in that chunk */
	i = offset >> PAGE_SHIFT;
	offset = offset & ~PAGE_MASK;

	while (size) {
		size_t n;
		chunksize = PAGE_SIZE;
		if (offset)
			chunksize -= offset;
		if (chunksize > size)
			chunksize = size;
		n = copy_page_to_iter(&page[i], offset, chunksize, to);
		copied += n;
		if (n != chunksize)
			return copied;
		offset = 0;
		size -= chunksize;
		i++;
	}
	return copied;
}