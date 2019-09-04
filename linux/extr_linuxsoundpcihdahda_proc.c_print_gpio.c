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
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  afg; } ;
struct hda_codec {int /*<<< orphan*/  nids; int /*<<< orphan*/  mixers; TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_GPIO_IO_COUNT ; 
 unsigned int AC_GPIO_I_COUNT ; 
 unsigned int AC_GPIO_I_COUNT_SHIFT ; 
 unsigned int AC_GPIO_O_COUNT ; 
 unsigned int AC_GPIO_O_COUNT_SHIFT ; 
 unsigned int AC_GPIO_UNSOLICITED ; 
 unsigned int AC_GPIO_WAKE ; 
 int /*<<< orphan*/  AC_PAR_GPIO_CAP ; 
 int /*<<< orphan*/  AC_VERB_GET_GPIO_DATA ; 
 int /*<<< orphan*/  AC_VERB_GET_GPIO_DIRECTION ; 
 int /*<<< orphan*/  AC_VERB_GET_GPIO_MASK ; 
 int /*<<< orphan*/  AC_VERB_GET_GPIO_STICKY_MASK ; 
 int /*<<< orphan*/  AC_VERB_GET_GPIO_UNSOLICITED_RSP_MASK ; 
 int /*<<< orphan*/  AC_VERB_GET_GPIO_WAKE_MASK ; 
 unsigned int param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_nid_array (struct snd_info_buffer*,struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int,int,int,int,...) ; 

__attribute__((used)) static void print_gpio(struct snd_info_buffer *buffer,
		       struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int gpio =
		param_read(codec, codec->core.afg, AC_PAR_GPIO_CAP);
	unsigned int enable, direction, wake, unsol, sticky, data;
	int i, max;
	snd_iprintf(buffer, "GPIO: io=%d, o=%d, i=%d, "
		    "unsolicited=%d, wake=%d\n",
		    gpio & AC_GPIO_IO_COUNT,
		    (gpio & AC_GPIO_O_COUNT) >> AC_GPIO_O_COUNT_SHIFT,
		    (gpio & AC_GPIO_I_COUNT) >> AC_GPIO_I_COUNT_SHIFT,
		    (gpio & AC_GPIO_UNSOLICITED) ? 1 : 0,
		    (gpio & AC_GPIO_WAKE) ? 1 : 0);
	max = gpio & AC_GPIO_IO_COUNT;
	if (!max || max > 8)
		return;
	enable = snd_hda_codec_read(codec, nid, 0,
				    AC_VERB_GET_GPIO_MASK, 0);
	direction = snd_hda_codec_read(codec, nid, 0,
				       AC_VERB_GET_GPIO_DIRECTION, 0);
	wake = snd_hda_codec_read(codec, nid, 0,
				  AC_VERB_GET_GPIO_WAKE_MASK, 0);
	unsol  = snd_hda_codec_read(codec, nid, 0,
				    AC_VERB_GET_GPIO_UNSOLICITED_RSP_MASK, 0);
	sticky = snd_hda_codec_read(codec, nid, 0,
				    AC_VERB_GET_GPIO_STICKY_MASK, 0);
	data = snd_hda_codec_read(codec, nid, 0,
				  AC_VERB_GET_GPIO_DATA, 0);
	for (i = 0; i < max; ++i)
		snd_iprintf(buffer,
			    "  IO[%d]: enable=%d, dir=%d, wake=%d, "
			    "sticky=%d, data=%d, unsol=%d\n", i,
			    (enable & (1<<i)) ? 1 : 0,
			    (direction & (1<<i)) ? 1 : 0,
			    (wake & (1<<i)) ? 1 : 0,
			    (sticky & (1<<i)) ? 1 : 0,
			    (data & (1<<i)) ? 1 : 0,
			    (unsol & (1<<i)) ? 1 : 0);
	/* FIXME: add GPO and GPI pin information */
	print_nid_array(buffer, codec, nid, &codec->mixers);
	print_nid_array(buffer, codec, nid, &codec->nids);
}