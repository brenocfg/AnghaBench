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
struct TYPE_2__ {int addr; } ;
struct hda_codec {int /*<<< orphan*/  card; TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  print_codec_info ; 
 int snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int snd_hda_codec_proc_new(struct hda_codec *codec)
{
	char name[32];

	snprintf(name, sizeof(name), "codec#%d", codec->core.addr);
	return snd_card_ro_proc_new(codec->card, name, codec, print_codec_info);
}