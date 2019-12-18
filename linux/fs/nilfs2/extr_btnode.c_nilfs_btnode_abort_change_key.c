#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nilfs_btnode_chkey_ctxt {scalar_t__ oldkey; scalar_t__ newkey; TYPE_1__* bh; struct buffer_head* newbh; } ;
struct buffer_head {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,scalar_t__) ; 

void nilfs_btnode_abort_change_key(struct address_space *btnc,
				   struct nilfs_btnode_chkey_ctxt *ctxt)
{
	struct buffer_head *nbh = ctxt->newbh;
	__u64 oldkey = ctxt->oldkey, newkey = ctxt->newkey;

	if (oldkey == newkey)
		return;

	if (nbh == NULL) {	/* blocksize == pagesize */
		xa_erase_irq(&btnc->i_pages, newkey);
		unlock_page(ctxt->bh->b_page);
	} else
		brelse(nbh);
}