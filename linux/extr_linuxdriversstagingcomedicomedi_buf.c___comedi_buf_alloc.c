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
struct page {int /*<<< orphan*/  flags; } ;
struct comedi_subdevice {scalar_t__ async_dma_dir; int /*<<< orphan*/  spin_lock; struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  hw_dev; int /*<<< orphan*/  class_dev; } ;
struct comedi_buf_page {void* virt_addr; } ;
struct comedi_buf_map {scalar_t__ dma_dir; unsigned int n_pages; struct comedi_buf_page* page_list; int /*<<< orphan*/  dma_hw_dev; int /*<<< orphan*/  refcount; } ;
struct comedi_async {int /*<<< orphan*/  prealloc_buf; struct comedi_buf_map* buf_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_PAGE_PROTECTION ; 
 int /*<<< orphan*/  CONFIG_HAS_DMA ; 
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_reserved ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct comedi_buf_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 
 struct page* virt_to_page (void*) ; 
 struct page** vmalloc (int) ; 
 int /*<<< orphan*/  vmap (struct page**,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct comedi_buf_page* vzalloc (int) ; 

__attribute__((used)) static void __comedi_buf_alloc(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       unsigned int n_pages)
{
	struct comedi_async *async = s->async;
	struct page **pages = NULL;
	struct comedi_buf_map *bm;
	struct comedi_buf_page *buf;
	unsigned long flags;
	unsigned int i;

	if (!IS_ENABLED(CONFIG_HAS_DMA) && s->async_dma_dir != DMA_NONE) {
		dev_err(dev->class_dev,
			"dma buffer allocation not supported\n");
		return;
	}

	bm = kzalloc(sizeof(*async->buf_map), GFP_KERNEL);
	if (!bm)
		return;

	kref_init(&bm->refcount);
	spin_lock_irqsave(&s->spin_lock, flags);
	async->buf_map = bm;
	spin_unlock_irqrestore(&s->spin_lock, flags);
	bm->dma_dir = s->async_dma_dir;
	if (bm->dma_dir != DMA_NONE)
		/* Need ref to hardware device to free buffer later. */
		bm->dma_hw_dev = get_device(dev->hw_dev);

	bm->page_list = vzalloc(sizeof(*buf) * n_pages);
	if (bm->page_list)
		pages = vmalloc(sizeof(struct page *) * n_pages);

	if (!pages)
		return;

	for (i = 0; i < n_pages; i++) {
		buf = &bm->page_list[i];
		if (bm->dma_dir != DMA_NONE)
#ifdef CONFIG_HAS_DMA
			buf->virt_addr = dma_alloc_coherent(bm->dma_hw_dev,
							    PAGE_SIZE,
							    &buf->dma_addr,
							    GFP_KERNEL |
							    __GFP_COMP);
#else
			break;
#endif
		else
			buf->virt_addr = (void *)get_zeroed_page(GFP_KERNEL);
		if (!buf->virt_addr)
			break;

		set_bit(PG_reserved, &(virt_to_page(buf->virt_addr)->flags));

		pages[i] = virt_to_page(buf->virt_addr);
	}
	spin_lock_irqsave(&s->spin_lock, flags);
	bm->n_pages = i;
	spin_unlock_irqrestore(&s->spin_lock, flags);

	/* vmap the prealloc_buf if all the pages were allocated */
	if (i == n_pages)
		async->prealloc_buf = vmap(pages, n_pages, VM_MAP,
					   COMEDI_PAGE_PROTECTION);

	vfree(pages);
}