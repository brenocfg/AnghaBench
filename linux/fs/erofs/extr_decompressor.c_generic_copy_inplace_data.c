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
typedef  void u8 ;
struct z_erofs_decompress_req {unsigned int inputsize; struct page** in; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 void* erofs_get_pcpubuf (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static void *generic_copy_inplace_data(struct z_erofs_decompress_req *rq,
				       u8 *src, unsigned int pageofs_in)
{
	/*
	 * if in-place decompression is ongoing, those decompressed
	 * pages should be copied in order to avoid being overlapped.
	 */
	struct page **in = rq->in;
	u8 *const tmp = erofs_get_pcpubuf(0);
	u8 *tmpp = tmp;
	unsigned int inlen = rq->inputsize - pageofs_in;
	unsigned int count = min_t(uint, inlen, PAGE_SIZE - pageofs_in);

	while (tmpp < tmp + inlen) {
		if (!src)
			src = kmap_atomic(*in);
		memcpy(tmpp, src + pageofs_in, count);
		kunmap_atomic(src);
		src = NULL;
		tmpp += count;
		pageofs_in = 0;
		count = PAGE_SIZE;
		++in;
	}
	return tmp;
}