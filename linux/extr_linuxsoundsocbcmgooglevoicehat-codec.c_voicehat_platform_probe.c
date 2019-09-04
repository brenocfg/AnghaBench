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
struct voicehat_priv {int /*<<< orphan*/  sdmode_delay_jiffies; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SDMODE_DELAY_MS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct voicehat_priv*) ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 struct voicehat_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  voicehat_component_driver ; 
 int /*<<< orphan*/  voicehat_dai ; 

__attribute__((used)) static int voicehat_platform_probe(struct platform_device *pdev)
{
	struct voicehat_priv *voicehat;
	unsigned int sdmode_delay;
	int ret;

	voicehat = devm_kzalloc(&pdev->dev, sizeof(*voicehat), GFP_KERNEL);
	if (!voicehat)
		return -ENOMEM;

	ret = device_property_read_u32(&pdev->dev, "voicehat_sdmode_delay",
				       &sdmode_delay);

	if (ret) {
		sdmode_delay = SDMODE_DELAY_MS;
		dev_info(&pdev->dev,
			 "property 'voicehat_sdmode_delay' not found default 5 mS");
	} else {
		dev_info(&pdev->dev, "property 'voicehat_sdmode_delay' found delay= %d mS",
			 sdmode_delay);
	}
	voicehat->sdmode_delay_jiffies = msecs_to_jiffies(sdmode_delay);

	dev_set_drvdata(&pdev->dev, voicehat);

	return snd_soc_register_component(&pdev->dev,
					  &voicehat_component_driver,
					  &voicehat_dai,
					  1);
}