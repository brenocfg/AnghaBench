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
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int skl_hda_hdmi_jack_init (struct snd_soc_card*) ; 

__attribute__((used)) static int skl_hda_card_late_probe(struct snd_soc_card *card)
{
	return skl_hda_hdmi_jack_init(card);
}