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
struct isi_board {int /*<<< orphan*/  flags; int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlock_card(struct isi_board *card)
{
	spin_unlock_irqrestore(&card->card_lock, card->flags);
}