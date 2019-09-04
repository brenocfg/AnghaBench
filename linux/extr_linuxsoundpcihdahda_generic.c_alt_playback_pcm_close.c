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
struct hda_gen_spec {int active_streams; int /*<<< orphan*/  pcm_mutex; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_GEN_PCM_ACT_CLOSE ; 
 int STREAM_INDEP_HP ; 
 int /*<<< orphan*/  call_pcm_playback_hook (struct hda_pcm_stream*,struct hda_codec*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alt_playback_pcm_close(struct hda_pcm_stream *hinfo,
				  struct hda_codec *codec,
				  struct snd_pcm_substream *substream)
{
	struct hda_gen_spec *spec = codec->spec;
	mutex_lock(&spec->pcm_mutex);
	spec->active_streams &= ~(1 << STREAM_INDEP_HP);
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_CLOSE);
	mutex_unlock(&spec->pcm_mutex);
	return 0;
}