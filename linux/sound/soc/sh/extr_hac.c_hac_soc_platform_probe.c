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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hac_ac97_ops ; 
 int /*<<< orphan*/  sh4_hac_component ; 
 int /*<<< orphan*/  sh4_hac_dai ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hac_soc_platform_probe(struct platform_device *pdev)
{
	int ret;

	ret = snd_soc_set_ac97_ops(&hac_ac97_ops);
	if (ret != 0)
		return ret;

	return devm_snd_soc_register_component(&pdev->dev, &sh4_hac_component,
					  sh4_hac_dai, ARRAY_SIZE(sh4_hac_dai));
}