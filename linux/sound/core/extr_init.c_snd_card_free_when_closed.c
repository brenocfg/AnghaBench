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
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int snd_card_disconnect (struct snd_card*) ; 

int snd_card_free_when_closed(struct snd_card *card)
{
	int ret = snd_card_disconnect(card);
	if (ret)
		return ret;
	put_device(&card->card_dev);
	return 0;
}