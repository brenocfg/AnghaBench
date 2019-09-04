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
struct snd_card {int dummy; } ;
struct TYPE_2__ {struct snd_card* alsa_card; } ;

/* Variables and functions */
 TYPE_1__* aoa_card ; 

struct snd_card *aoa_get_card(void)
{
	if (aoa_card)
		return aoa_card->alsa_card;
	return NULL;
}