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
struct snd_rme9652 {int dummy; } ;
struct snd_card {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rme9652_free (struct snd_rme9652*) ; 

__attribute__((used)) static void snd_rme9652_card_free(struct snd_card *card)
{
	struct snd_rme9652 *rme9652 = (struct snd_rme9652 *) card->private_data;

	if (rme9652)
		snd_rme9652_free(rme9652);
}