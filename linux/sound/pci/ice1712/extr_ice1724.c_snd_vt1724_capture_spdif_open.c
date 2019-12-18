#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; void* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* open ) (struct snd_ice1712*,struct snd_pcm_substream*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct snd_ice1712 {TYPE_2__ spdif; scalar_t__ force_rdma1; struct snd_pcm_substream* capture_con_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  VT1724_BUFFER_ALIGN ; 
 int /*<<< orphan*/  constrain_rate_if_locked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  set_rate_constraints (struct snd_ice1712*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_vt1724_2ch_stereo ; 
 int /*<<< orphan*/  snd_vt1724_spdif ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vt1724_capture_spdif_reg ; 

__attribute__((used)) static int snd_vt1724_capture_spdif_open(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	runtime->private_data = (void *)&vt1724_capture_spdif_reg;
	ice->capture_con_substream = substream;
	if (ice->force_rdma1) {
		runtime->hw = snd_vt1724_2ch_stereo;
		set_rate_constraints(ice, substream);
	} else
		runtime->hw = snd_vt1724_spdif;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   VT1724_BUFFER_ALIGN);
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   VT1724_BUFFER_ALIGN);
	constrain_rate_if_locked(substream);
	if (ice->spdif.ops.open)
		ice->spdif.ops.open(ice, substream);
	return 0;
}