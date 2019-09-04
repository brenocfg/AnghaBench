#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  alsa_card; } ;

/* Variables and functions */
 TYPE_1__* aoa_card ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 

void aoa_alsa_cleanup(void)
{
	if (aoa_card) {
		snd_card_free(aoa_card->alsa_card);
		aoa_card = NULL;
	}
}