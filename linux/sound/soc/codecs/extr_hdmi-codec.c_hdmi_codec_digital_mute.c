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
struct TYPE_6__ {int /*<<< orphan*/  data; TYPE_1__* ops; } ;
struct hdmi_codec_priv {TYPE_3__ hcd; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int (* digital_mute ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct hdmi_codec_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdmi_codec_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);

	if (hcp->hcd.ops->digital_mute)
		return hcp->hcd.ops->digital_mute(dai->dev->parent,
						  hcp->hcd.data, mute);

	return 0;
}