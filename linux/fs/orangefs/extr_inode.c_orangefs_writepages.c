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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct orangefs_writepages {int maxpages; struct orangefs_writepages* bv; struct orangefs_writepages* pages; scalar_t__ npages; } ;
struct blk_plug {int dummy; } ;
struct bio_vec {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct orangefs_writepages*) ; 
 struct orangefs_writepages* kzalloc (int,int /*<<< orphan*/ ) ; 
 int orangefs_bufmap_size_query () ; 
 int /*<<< orphan*/  orangefs_writepages_callback ; 
 int orangefs_writepages_work (struct orangefs_writepages*,struct writeback_control*) ; 
 int write_cache_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ,struct orangefs_writepages*) ; 

__attribute__((used)) static int orangefs_writepages(struct address_space *mapping,
    struct writeback_control *wbc)
{
	struct orangefs_writepages *ow;
	struct blk_plug plug;
	int ret;
	ow = kzalloc(sizeof(struct orangefs_writepages), GFP_KERNEL);
	if (!ow)
		return -ENOMEM;
	ow->maxpages = orangefs_bufmap_size_query()/PAGE_SIZE;
	ow->pages = kcalloc(ow->maxpages, sizeof(struct page *), GFP_KERNEL);
	if (!ow->pages) {
		kfree(ow);
		return -ENOMEM;
	}
	ow->bv = kcalloc(ow->maxpages, sizeof(struct bio_vec), GFP_KERNEL);
	if (!ow->bv) {
		kfree(ow->pages);
		kfree(ow);
		return -ENOMEM;
	}
	blk_start_plug(&plug);
	ret = write_cache_pages(mapping, wbc, orangefs_writepages_callback, ow);
	if (ow->npages)
		ret = orangefs_writepages_work(ow, wbc);
	blk_finish_plug(&plug);
	kfree(ow->pages);
	kfree(ow->bv);
	kfree(ow);
	return ret;
}