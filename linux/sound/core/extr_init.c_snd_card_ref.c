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
struct snd_card {int /*<<< orphan*/  card_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_mutex ; 
 struct snd_card** snd_cards ; 

struct snd_card *snd_card_ref(int idx)
{
	struct snd_card *card;

	mutex_lock(&snd_card_mutex);
	card = snd_cards[idx];
	if (card)
		get_device(&card->card_dev);
	mutex_unlock(&snd_card_mutex);
	return card;
}