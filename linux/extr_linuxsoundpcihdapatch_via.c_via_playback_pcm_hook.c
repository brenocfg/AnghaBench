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
struct snd_pcm_substream {int dummy; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  analog_low_current_mode (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1708_update_hp_work (struct hda_codec*) ; 

__attribute__((used)) static void via_playback_pcm_hook(struct hda_pcm_stream *hinfo,
				  struct hda_codec *codec,
				  struct snd_pcm_substream *substream,
				  int action)
{
	analog_low_current_mode(codec);
	vt1708_update_hp_work(codec);
}