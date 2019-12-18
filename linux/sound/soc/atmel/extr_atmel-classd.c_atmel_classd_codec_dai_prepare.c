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
 int /*<<< orphan*/  CLASSD_MR ; 
 int CLASSD_MR_LEN_DIS ; 
 int CLASSD_MR_LEN_MASK ; 
 int CLASSD_MR_LEN_SHIFT ; 
 int CLASSD_MR_REN_DIS ; 
 int CLASSD_MR_REN_MASK ; 
 int CLASSD_MR_REN_SHIFT ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int atmel_classd_codec_dai_prepare(struct snd_pcm_substream *substream,
					struct snd_soc_dai *codec_dai)
{
	struct snd_soc_component *component = codec_dai->component;

	snd_soc_component_update_bits(component, CLASSD_MR,
				CLASSD_MR_LEN_MASK | CLASSD_MR_REN_MASK,
				(CLASSD_MR_LEN_DIS << CLASSD_MR_LEN_SHIFT)
				|(CLASSD_MR_REN_DIS << CLASSD_MR_REN_SHIFT));

	return 0;
}