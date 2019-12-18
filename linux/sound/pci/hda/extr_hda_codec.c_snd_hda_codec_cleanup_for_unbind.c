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
struct hda_codec {int /*<<< orphan*/  core; int /*<<< orphan*/  nids; int /*<<< orphan*/  mixers; scalar_t__ spdif_status_reset; int /*<<< orphan*/ * slave_dig_outs; int /*<<< orphan*/ * preset; int /*<<< orphan*/  verbs; int /*<<< orphan*/  spdif_out; int /*<<< orphan*/  cvt_setups; int /*<<< orphan*/  driver_pins; int /*<<< orphan*/ * spec; int /*<<< orphan*/ * proc_widget_hook; int /*<<< orphan*/  patch_ops; int /*<<< orphan*/  in_freeing; int /*<<< orphan*/  jackpoll_work; scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codec_release_pcms (struct hda_codec*) ; 
 int /*<<< orphan*/  hda_codec_dev (struct hda_codec*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_conn_list (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_array_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_ctls_clear (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_detach_beep_device (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_jack_tbl_clear (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hdac_regmap_exit (int /*<<< orphan*/ *) ; 

void snd_hda_codec_cleanup_for_unbind(struct hda_codec *codec)
{
	if (codec->registered) {
		/* pm_runtime_put() is called in snd_hdac_device_exit() */
		pm_runtime_get_noresume(hda_codec_dev(codec));
		pm_runtime_disable(hda_codec_dev(codec));
		codec->registered = 0;
	}

	cancel_delayed_work_sync(&codec->jackpoll_work);
	if (!codec->in_freeing)
		snd_hda_ctls_clear(codec);
	codec_release_pcms(codec);
	snd_hda_detach_beep_device(codec);
	memset(&codec->patch_ops, 0, sizeof(codec->patch_ops));
	snd_hda_jack_tbl_clear(codec);
	codec->proc_widget_hook = NULL;
	codec->spec = NULL;

	/* free only driver_pins so that init_pins + user_pins are restored */
	snd_array_free(&codec->driver_pins);
	snd_array_free(&codec->cvt_setups);
	snd_array_free(&codec->spdif_out);
	snd_array_free(&codec->verbs);
	codec->preset = NULL;
	codec->slave_dig_outs = NULL;
	codec->spdif_status_reset = 0;
	snd_array_free(&codec->mixers);
	snd_array_free(&codec->nids);
	remove_conn_list(codec);
	snd_hdac_regmap_exit(&codec->core);
}