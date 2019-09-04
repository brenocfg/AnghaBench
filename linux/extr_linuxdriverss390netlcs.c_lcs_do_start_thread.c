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
typedef  int /*<<< orphan*/  u8 ;
struct lcs_card {unsigned long thread_start_mask; int /*<<< orphan*/  mask_lock; scalar_t__ thread_running_mask; scalar_t__ thread_allowed_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_do_start_thread(struct lcs_card *card, unsigned long thread)
{
        unsigned long flags;
        int rc = 0;

	spin_lock_irqsave(&card->mask_lock, flags);
        LCS_DBF_TEXT_(4, trace, "  %02x%02x%02x",
                        (u8) card->thread_start_mask,
                        (u8) card->thread_allowed_mask,
                        (u8) card->thread_running_mask);
        rc = (card->thread_start_mask & thread);
	spin_unlock_irqrestore(&card->mask_lock, flags);
        return rc;
}