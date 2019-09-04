#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {char* name; char* stream_name; int dai_fmt; struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
 int SND_SOC_DAIFMT_I2S ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd_rpi_i_sabre_q2m ; 
 struct snd_soc_dai_link* snd_rpi_i_sabre_q2m_dai ; 
 int snd_soc_register_card (TYPE_1__*) ; 

__attribute__((used)) static int snd_rpi_i_sabre_q2m_probe(struct platform_device *pdev)
{
	int ret = 0;

	snd_rpi_i_sabre_q2m.dev = &pdev->dev;
	if (pdev->dev.of_node) {
		struct device_node *i2s_node;
		struct snd_soc_dai_link *dai;

		dai = &snd_rpi_i_sabre_q2m_dai[0];
		i2s_node = of_parse_phandle(pdev->dev.of_node,
							"i2s-controller", 0);
		if (i2s_node) {
			dai->cpu_dai_name     = NULL;
			dai->cpu_of_node      = i2s_node;
			dai->platform_name    = NULL;
			dai->platform_of_node = i2s_node;
		} else {
			dev_err(&pdev->dev,
			    "Property 'i2s-controller' missing or invalid\n");
			return (-EINVAL);
		}

		dai->name        = "I-Sabre Q2M";
		dai->stream_name = "I-Sabre Q2M DAC";
		dai->dai_fmt     = SND_SOC_DAIFMT_I2S
					| SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBS_CFS;
	}

	/* Wait for registering codec driver */
	mdelay(50);

	ret = snd_soc_register_card(&snd_rpi_i_sabre_q2m);
	if (ret) {
		dev_err(&pdev->dev,
			"snd_soc_register_card() failed: %d\n", ret);
	}

	return ret;
}