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
struct snd_soc_pcm_runtime {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dvc {int /*<<< orphan*/  rdown; int /*<<< orphan*/  rup; int /*<<< orphan*/  ren; int /*<<< orphan*/  mute; int /*<<< orphan*/  volume; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOLUME_RAMP_MAX_DVC ; 
 int /*<<< orphan*/  rsnd_dvc_volume_update ; 
 int rsnd_io_is_play (struct rsnd_dai_stream*) ; 
 struct rsnd_dai* rsnd_io_to_rdai (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_kctrl_accept_anytime ; 
 int rsnd_kctrl_new_e (struct rsnd_mod*,struct rsnd_dai_stream*,struct snd_soc_pcm_runtime*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rsnd_kctrl_new_m (struct rsnd_mod*,struct rsnd_dai_stream*,struct snd_soc_pcm_runtime*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int rsnd_kctrl_new_s (struct rsnd_mod*,struct rsnd_dai_stream*,struct snd_soc_pcm_runtime*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct rsnd_dvc* rsnd_mod_to_dvc (struct rsnd_mod*) ; 
 int rsnd_rdai_channels_get (struct rsnd_dai*) ; 
 int /*<<< orphan*/  volume_ramp_rate ; 

__attribute__((used)) static int rsnd_dvc_pcm_new(struct rsnd_mod *mod,
			    struct rsnd_dai_stream *io,
			    struct snd_soc_pcm_runtime *rtd)
{
	struct rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	struct rsnd_dai *rdai = rsnd_io_to_rdai(io);
	int is_play = rsnd_io_is_play(io);
	int channels = rsnd_rdai_channels_get(rdai);
	int ret;

	/* Volume */
	ret = rsnd_kctrl_new_m(mod, io, rtd,
			is_play ?
			"DVC Out Playback Volume" : "DVC In Capture Volume",
			rsnd_kctrl_accept_anytime,
			rsnd_dvc_volume_update,
			&dvc->volume, channels,
			0x00800000 - 1);
	if (ret < 0)
		return ret;

	/* Mute */
	ret = rsnd_kctrl_new_m(mod, io, rtd,
			is_play ?
			"DVC Out Mute Switch" : "DVC In Mute Switch",
			rsnd_kctrl_accept_anytime,
			rsnd_dvc_volume_update,
			&dvc->mute, channels,
			1);
	if (ret < 0)
		return ret;

	/* Ramp */
	ret = rsnd_kctrl_new_s(mod, io, rtd,
			is_play ?
			"DVC Out Ramp Switch" : "DVC In Ramp Switch",
			rsnd_kctrl_accept_anytime,
			rsnd_dvc_volume_update,
			&dvc->ren, 1);
	if (ret < 0)
		return ret;

	ret = rsnd_kctrl_new_e(mod, io, rtd,
			is_play ?
			"DVC Out Ramp Up Rate" : "DVC In Ramp Up Rate",
			rsnd_kctrl_accept_anytime,
			rsnd_dvc_volume_update,
			&dvc->rup,
			volume_ramp_rate,
			VOLUME_RAMP_MAX_DVC);
	if (ret < 0)
		return ret;

	ret = rsnd_kctrl_new_e(mod, io, rtd,
			is_play ?
			"DVC Out Ramp Down Rate" : "DVC In Ramp Down Rate",
			rsnd_kctrl_accept_anytime,
			rsnd_dvc_volume_update,
			&dvc->rdown,
			volume_ramp_rate,
			VOLUME_RAMP_MAX_DVC);

	if (ret < 0)
		return ret;

	return 0;
}