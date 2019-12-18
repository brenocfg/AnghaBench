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
struct hda_codec {scalar_t__ beep; int /*<<< orphan*/  card; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,scalar_t__) ; 

void snd_hda_detach_beep_device(struct hda_codec *codec)
{
	if (!codec->bus->shutdown && codec->beep)
		snd_device_free(codec->card, codec->beep);
}