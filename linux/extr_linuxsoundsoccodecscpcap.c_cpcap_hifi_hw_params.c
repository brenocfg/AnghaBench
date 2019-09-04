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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cpcap_audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_DAI_HIFI ; 
 int cpcap_set_samprate (struct cpcap_audio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct cpcap_audio* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cpcap_hifi_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	int rate = params_rate(params);

	dev_dbg(component->dev, "HiFi setup HW params: rate=%d", rate);
	return cpcap_set_samprate(cpcap, CPCAP_DAI_HIFI, rate);
}