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
struct snd_interwave {scalar_t__ irq; int /*<<< orphan*/  i2c_res; } ;
struct snd_card {struct snd_interwave* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_interwave_free(struct snd_card *card)
{
	struct snd_interwave *iwcard = card->private_data;

	if (iwcard == NULL)
		return;
#ifdef SNDRV_STB
	release_and_free_resource(iwcard->i2c_res);
#endif
	if (iwcard->irq >= 0)
		free_irq(iwcard->irq, (void *)iwcard);
}