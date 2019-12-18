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
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dummy_codec ; 
 int /*<<< orphan*/  dummy_dai ; 
 int /*<<< orphan*/  dummy_platform ; 

__attribute__((used)) static int snd_soc_dummy_probe(struct platform_device *pdev)
{
	int ret;

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &dummy_codec, &dummy_dai, 1);
	if (ret < 0)
		return ret;

	ret = devm_snd_soc_register_component(&pdev->dev, &dummy_platform,
					      NULL, 0);

	return ret;
}