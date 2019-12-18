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
struct balloon_dev_info {int /*<<< orphan*/  pages_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  balloon_page_enqueue_one (struct balloon_dev_info*,struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void balloon_page_enqueue(struct balloon_dev_info *b_dev_info,
			  struct page *page)
{
	unsigned long flags;

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	balloon_page_enqueue_one(b_dev_info, page);
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);
}