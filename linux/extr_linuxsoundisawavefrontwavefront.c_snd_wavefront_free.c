#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_card {scalar_t__ private_data; } ;
struct TYPE_3__ {scalar_t__ irq; int /*<<< orphan*/  res_base; } ;
struct TYPE_4__ {TYPE_1__ wavefront; } ;
typedef  TYPE_2__ snd_wavefront_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_wavefront_free(struct snd_card *card)
{
	snd_wavefront_card_t *acard = (snd_wavefront_card_t *)card->private_data;
	
	if (acard) {
		release_and_free_resource(acard->wavefront.res_base);
		if (acard->wavefront.irq > 0)
			free_irq(acard->wavefront.irq, (void *)acard);
	}
}