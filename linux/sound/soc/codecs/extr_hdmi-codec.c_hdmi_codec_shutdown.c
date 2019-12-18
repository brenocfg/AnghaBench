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
struct snd_soc_dai {TYPE_2__* dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; TYPE_1__* ops; } ;
struct hdmi_codec_priv {int /*<<< orphan*/  busy; TYPE_3__ hcd; int /*<<< orphan*/  chmap_idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* audio_shutdown ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CODEC_CHMAP_IDX_UNKNOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hdmi_codec_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_codec_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);

	hcp->chmap_idx = HDMI_CODEC_CHMAP_IDX_UNKNOWN;
	hcp->hcd.ops->audio_shutdown(dai->dev->parent, hcp->hcd.data);

	clear_bit(0, &hcp->busy);
}