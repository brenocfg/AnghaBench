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
struct snd_card {int /*<<< orphan*/  files_lock; int /*<<< orphan*/  files_list; int /*<<< orphan*/  remove_sleep; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int snd_card_disconnect (struct snd_card*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_card_disconnect_sync(struct snd_card *card)
{
	int err;

	err = snd_card_disconnect(card);
	if (err < 0) {
		dev_err(card->dev,
			"snd_card_disconnect error (%d), skipping sync\n",
			err);
		return;
	}

	spin_lock_irq(&card->files_lock);
	wait_event_lock_irq(card->remove_sleep,
			    list_empty(&card->files_list),
			    card->files_lock);
	spin_unlock_irq(&card->files_lock);
}