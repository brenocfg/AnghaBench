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
struct z_erofs_decompressor {int (* decompress ) (struct z_erofs_decompress_req*,void*) ;int (* prepare_destpages ) (struct z_erofs_decompress_req*,struct list_head*) ;} ;
struct z_erofs_decompress_req {int pageofs_out; int outputsize; int inplace_io; int /*<<< orphan*/ * out; int /*<<< orphan*/  alg; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (void*) ; 
 unsigned int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  copy_from_pcpubuf (int /*<<< orphan*/ *,void*,int,int) ; 
 struct z_erofs_decompressor* decompressors ; 
 void* erofs_get_pcpubuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_put_pcpubuf (void*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int stub1 (struct z_erofs_decompress_req*,void*) ; 
 int stub2 (struct z_erofs_decompress_req*,struct list_head*) ; 
 int stub3 (struct z_erofs_decompress_req*,void*) ; 
 void* vm_map_ram (int /*<<< orphan*/ *,unsigned int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_unmap_aliases () ; 
 int /*<<< orphan*/  vm_unmap_ram (void*,unsigned int const) ; 

__attribute__((used)) static int z_erofs_decompress_generic(struct z_erofs_decompress_req *rq,
				      struct list_head *pagepool)
{
	const unsigned int nrpages_out =
		PAGE_ALIGN(rq->pageofs_out + rq->outputsize) >> PAGE_SHIFT;
	const struct z_erofs_decompressor *alg = decompressors + rq->alg;
	unsigned int dst_maptype;
	void *dst;
	int ret, i;

	if (nrpages_out == 1 && !rq->inplace_io) {
		DBG_BUGON(!*rq->out);
		dst = kmap_atomic(*rq->out);
		dst_maptype = 0;
		goto dstmap_out;
	}

	/*
	 * For the case of small output size (especially much less
	 * than PAGE_SIZE), memcpy the decompressed data rather than
	 * compressed data is preferred.
	 */
	if (rq->outputsize <= PAGE_SIZE * 7 / 8) {
		dst = erofs_get_pcpubuf(0);
		if (IS_ERR(dst))
			return PTR_ERR(dst);

		rq->inplace_io = false;
		ret = alg->decompress(rq, dst);
		if (!ret)
			copy_from_pcpubuf(rq->out, dst, rq->pageofs_out,
					  rq->outputsize);

		erofs_put_pcpubuf(dst);
		return ret;
	}

	ret = alg->prepare_destpages(rq, pagepool);
	if (ret < 0) {
		return ret;
	} else if (ret) {
		dst = page_address(*rq->out);
		dst_maptype = 1;
		goto dstmap_out;
	}

	i = 0;
	while (1) {
		dst = vm_map_ram(rq->out, nrpages_out, -1, PAGE_KERNEL);

		/* retry two more times (totally 3 times) */
		if (dst || ++i >= 3)
			break;
		vm_unmap_aliases();
	}

	if (!dst)
		return -ENOMEM;

	dst_maptype = 2;

dstmap_out:
	ret = alg->decompress(rq, dst + rq->pageofs_out);

	if (!dst_maptype)
		kunmap_atomic(dst);
	else if (dst_maptype == 2)
		vm_unmap_ram(dst, nrpages_out);
	return ret;
}