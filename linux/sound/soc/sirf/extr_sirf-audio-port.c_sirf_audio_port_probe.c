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
struct sirf_audio_port {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sirf_audio_port* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sirf_audio_port*) ; 
 int /*<<< orphan*/  sirf_audio_port_component ; 
 int /*<<< orphan*/  sirf_audio_port_dai ; 

__attribute__((used)) static int sirf_audio_port_probe(struct platform_device *pdev)
{
	int ret;
	struct sirf_audio_port *port;

	port = devm_kzalloc(&pdev->dev,
			sizeof(struct sirf_audio_port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	ret = devm_snd_soc_register_component(&pdev->dev,
			&sirf_audio_port_component, &sirf_audio_port_dai, 1);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, port);
	return devm_snd_dmaengine_pcm_register(&pdev->dev, NULL, 0);
}