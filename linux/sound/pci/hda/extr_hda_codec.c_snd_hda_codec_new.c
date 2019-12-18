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
struct snd_card {int dummy; } ;
struct hda_codec {int dummy; } ;
struct hda_bus {int dummy; } ;

/* Variables and functions */
 int snd_hda_codec_device_init (struct hda_bus*,struct snd_card*,unsigned int,struct hda_codec**) ; 
 int snd_hda_codec_device_new (struct hda_bus*,struct snd_card*,unsigned int,struct hda_codec*) ; 

int snd_hda_codec_new(struct hda_bus *bus, struct snd_card *card,
		      unsigned int codec_addr, struct hda_codec **codecp)
{
	int ret;

	ret = snd_hda_codec_device_init(bus, card, codec_addr, codecp);
	if (ret < 0)
		return ret;

	return snd_hda_codec_device_new(bus, card, codec_addr, *codecp);
}