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
struct snd_soc_dai_link {struct device_node* codec_of_node; struct device_node* platform_of_node; struct device_node* cpu_of_node; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai_link tse850_dailink ; 

__attribute__((used)) static int tse850_dt_init(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *codec_np, *cpu_np;
	struct snd_soc_dai_link *dailink = &tse850_dailink;

	if (!np) {
		dev_err(&pdev->dev, "only device tree supported\n");
		return -EINVAL;
	}

	cpu_np = of_parse_phandle(np, "axentia,cpu-dai", 0);
	if (!cpu_np) {
		dev_err(&pdev->dev, "failed to get cpu dai\n");
		return -EINVAL;
	}
	dailink->cpu_of_node = cpu_np;
	dailink->platform_of_node = cpu_np;
	of_node_put(cpu_np);

	codec_np = of_parse_phandle(np, "axentia,audio-codec", 0);
	if (!codec_np) {
		dev_err(&pdev->dev, "failed to get codec info\n");
		return -EINVAL;
	}
	dailink->codec_of_node = codec_np;
	of_node_put(codec_np);

	return 0;
}