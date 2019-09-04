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
struct mpage_readpage_args {int nr_pages; scalar_t__ bio; int /*<<< orphan*/  get_block; struct page* page; } ;
typedef  int /*<<< orphan*/  get_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ do_mpage_readpage (struct mpage_readpage_args*) ; 
 int /*<<< orphan*/  mpage_bio_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int mpage_readpage(struct page *page, get_block_t get_block)
{
	struct mpage_readpage_args args = {
		.page = page,
		.nr_pages = 1,
		.get_block = get_block,
	};

	args.bio = do_mpage_readpage(&args);
	if (args.bio)
		mpage_bio_submit(REQ_OP_READ, 0, args.bio);
	return 0;
}