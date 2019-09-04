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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (struct snd_ice1712*,struct snd_pcm_substream*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct snd_ice1712 {TYPE_2__ spdif; int /*<<< orphan*/ * capture_con_substream; int /*<<< orphan*/  pro_rate_default; } ;

/* Variables and functions */
 scalar_t__ PRO_RATE_RESET ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_vt1724_set_pro_rate (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_vt1724_capture_spdif_close(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	if (PRO_RATE_RESET)
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_default, 0);
	ice->capture_con_substream = NULL;
	if (ice->spdif.ops.close)
		ice->spdif.ops.close(ice, substream);

	return 0;
}