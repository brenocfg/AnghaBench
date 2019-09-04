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
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLV320AIC23_ACTIVE ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tlv320aic23_pcm_prepare(struct snd_pcm_substream *substream,
				   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;

	/* set active */
	snd_soc_component_write(component, TLV320AIC23_ACTIVE, 0x0001);

	return 0;
}