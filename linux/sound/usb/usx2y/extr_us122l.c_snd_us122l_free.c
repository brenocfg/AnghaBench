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
struct us122l {int card_index; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int SNDRV_CARDS ; 
 struct us122l* US122L (struct snd_card*) ; 
 scalar_t__* snd_us122l_card_used ; 

__attribute__((used)) static void snd_us122l_free(struct snd_card *card)
{
	struct us122l	*us122l = US122L(card);
	int		index = us122l->card_index;
	if (index >= 0  &&  index < SNDRV_CARDS)
		snd_us122l_card_used[index] = 0;
}