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
struct snd_card {struct completion* release_completion; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int snd_card_free_when_closed (struct snd_card*) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

int snd_card_free(struct snd_card *card)
{
	struct completion released;
	int ret;

	init_completion(&released);
	card->release_completion = &released;
	ret = snd_card_free_when_closed(card);
	if (ret)
		return ret;
	/* wait, until all devices are ready for the free operation */
	wait_for_completion(&released);
	return 0;
}