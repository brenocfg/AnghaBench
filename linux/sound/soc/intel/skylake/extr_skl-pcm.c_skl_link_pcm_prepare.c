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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_2__* runtime; int /*<<< orphan*/  stream; } ;
struct skl_module_cfg {TYPE_3__* pipe; } ;
struct skl_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  passthru; } ;
struct TYPE_5__ {TYPE_1__* status; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_XRUN ; 
 struct skl_dev* get_skl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_reset_pipe (struct skl_dev*,TYPE_3__*) ; 
 struct skl_module_cfg* skl_tplg_be_get_cpr_module (struct snd_soc_dai*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_link_pcm_prepare(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct skl_dev *skl = get_skl_ctx(dai->dev);
	struct skl_module_cfg *mconfig = NULL;

	/* In case of XRUN recovery, reset the FW pipe to clean state */
	mconfig = skl_tplg_be_get_cpr_module(dai, substream->stream);
	if (mconfig && !mconfig->pipe->passthru &&
		(substream->runtime->status->state == SNDRV_PCM_STATE_XRUN))
		skl_reset_pipe(skl, mconfig->pipe);

	return 0;
}