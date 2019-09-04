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

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dout (char*,int,int,...) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int,int) ; 

void ceph_zero_page_vector_range(int off, int len, struct page **pages)
{
	int i = off >> PAGE_SHIFT;

	off &= ~PAGE_MASK;

	dout("zero_page_vector_page %u~%u\n", off, len);

	/* leading partial page? */
	if (off) {
		int end = min((int)PAGE_SIZE, off + len);
		dout("zeroing %d %p head from %d\n", i, pages[i],
		     (int)off);
		zero_user_segment(pages[i], off, end);
		len -= (end - off);
		i++;
	}
	while (len >= PAGE_SIZE) {
		dout("zeroing %d %p len=%d\n", i, pages[i], len);
		zero_user_segment(pages[i], 0, PAGE_SIZE);
		len -= PAGE_SIZE;
		i++;
	}
	/* trailing partial page? */
	if (len) {
		dout("zeroing %d %p tail to %d\n", i, pages[i], (int)len);
		zero_user_segment(pages[i], 0, len);
	}
}