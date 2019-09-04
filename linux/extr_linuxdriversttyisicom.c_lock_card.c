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
struct isi_board {unsigned long base; int /*<<< orphan*/  flags; int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int inw (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int lock_card(struct isi_board *card)
{
	unsigned long base = card->base;
	unsigned int retries, a;

	for (retries = 0; retries < 10; retries++) {
		spin_lock_irqsave(&card->card_lock, card->flags);
		for (a = 0; a < 10; a++) {
			if (inw(base + 0xe) & 0x1)
				return 1;
			udelay(10);
		}
		spin_unlock_irqrestore(&card->card_lock, card->flags);
		msleep(10);
	}
	pr_warn("Failed to lock Card (0x%lx)\n", card->base);

	return 0;	/* Failed to acquire the card! */
}