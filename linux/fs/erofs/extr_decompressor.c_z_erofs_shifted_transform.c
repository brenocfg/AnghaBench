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
struct z_erofs_decompress_req {int pageofs_out; scalar_t__* out; scalar_t__* in; scalar_t__ outputsize; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EIO ; 
 unsigned int PAGE_ALIGN (scalar_t__) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 unsigned char* kmap_atomic (scalar_t__) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int const) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int z_erofs_shifted_transform(const struct z_erofs_decompress_req *rq,
				     struct list_head *pagepool)
{
	const unsigned int nrpages_out =
		PAGE_ALIGN(rq->pageofs_out + rq->outputsize) >> PAGE_SHIFT;
	const unsigned int righthalf = PAGE_SIZE - rq->pageofs_out;
	unsigned char *src, *dst;

	if (nrpages_out > 2) {
		DBG_BUGON(1);
		return -EIO;
	}

	if (rq->out[0] == *rq->in) {
		DBG_BUGON(nrpages_out != 1);
		return 0;
	}

	src = kmap_atomic(*rq->in);
	if (!rq->out[0]) {
		dst = NULL;
	} else {
		dst = kmap_atomic(rq->out[0]);
		memcpy(dst + rq->pageofs_out, src, righthalf);
	}

	if (rq->out[1] == *rq->in) {
		memmove(src, src + righthalf, rq->pageofs_out);
	} else if (nrpages_out == 2) {
		if (dst)
			kunmap_atomic(dst);
		DBG_BUGON(!rq->out[1]);
		dst = kmap_atomic(rq->out[1]);
		memcpy(dst, src + righthalf, rq->pageofs_out);
	}
	if (dst)
		kunmap_atomic(dst);
	kunmap_atomic(src);
	return 0;
}