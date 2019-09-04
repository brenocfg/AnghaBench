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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int rate_min; int rate_max; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_ice1712 {struct qtet_spec* spec; } ;
struct qtet_spec {int /*<<< orphan*/  ak4113; } ;

/* Variables and functions */
 scalar_t__ EXT_SPDIF_TYPE ; 
 scalar_t__ qtet_get_spdif_master_type (struct snd_ice1712*) ; 
 int snd_ak4113_external_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qtet_spdif_in_open(struct snd_ice1712 *ice,
		struct snd_pcm_substream *substream)
{
	struct qtet_spec *spec = ice->spec;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int rate;

	if (qtet_get_spdif_master_type(ice) != EXT_SPDIF_TYPE)
		/* not external SPDIF, no rate limitation */
		return;
	/* only external SPDIF can detect incoming sample rate */
	rate = snd_ak4113_external_rate(spec->ak4113);
	if (rate >= runtime->hw.rate_min && rate <= runtime->hw.rate_max) {
		runtime->hw.rate_min = rate;
		runtime->hw.rate_max = rate;
	}
}