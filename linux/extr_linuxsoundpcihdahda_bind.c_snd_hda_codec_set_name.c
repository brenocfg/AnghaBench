#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ addr; char* vendor_name; char* chip_name; } ;
struct hda_codec {TYPE_3__ core; TYPE_2__* bus; TYPE_1__* card; } ;
struct TYPE_5__ {scalar_t__ mixer_assigned; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mixername; } ;

/* Variables and functions */
 int snd_hdac_device_set_chip_name (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*,char*) ; 

int snd_hda_codec_set_name(struct hda_codec *codec, const char *name)
{
	int err;

	if (!name)
		return 0;
	err = snd_hdac_device_set_chip_name(&codec->core, name);
	if (err < 0)
		return err;

	/* update the mixer name */
	if (!*codec->card->mixername ||
	    codec->bus->mixer_assigned >= codec->core.addr) {
		snprintf(codec->card->mixername,
			 sizeof(codec->card->mixername), "%s %s",
			 codec->core.vendor_name, codec->core.chip_name);
		codec->bus->mixer_assigned = codec->core.addr;
	}

	return 0;
}