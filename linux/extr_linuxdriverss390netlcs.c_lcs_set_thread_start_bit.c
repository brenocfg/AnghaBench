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
struct lcs_card {unsigned long thread_allowed_mask; unsigned long thread_start_mask; int /*<<< orphan*/  mask_lock; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lcs_set_thread_start_bit(struct lcs_card *card, unsigned long thread)
{
        unsigned long flags;

	spin_lock_irqsave(&card->mask_lock, flags);
        if ( !(card->thread_allowed_mask & thread) ||
              (card->thread_start_mask & thread) ) {
                spin_unlock_irqrestore(&card->mask_lock, flags);
                return -EPERM;
        }
        card->thread_start_mask |= thread;
	spin_unlock_irqrestore(&card->mask_lock, flags);
        return 0;
}