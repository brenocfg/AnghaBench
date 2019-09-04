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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; } ;
struct snd_soc_component {TYPE_2__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISABRECODEC_REG_01 ; 
 int /*<<< orphan*/  ISABRECODEC_REG_02 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rpi_i_sabre_q2m_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	unsigned int value;

	/* Device ID */
	value = snd_soc_component_read32(component, ISABRECODEC_REG_01);
	dev_info(component->card->dev, "Audiophonics Device ID : %02X\n", value);

	/* API revision */
	value = snd_soc_component_read32(component, ISABRECODEC_REG_02);
	dev_info(component->card->dev, "Audiophonics API revision : %02X\n", value);

	return 0;
}