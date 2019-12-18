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
struct sst_pdata {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  byt_dai_component ; 
 int /*<<< orphan*/  byt_dais ; 
 struct sst_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_dsp_free (int /*<<< orphan*/ *,struct sst_pdata*) ; 
 int sst_byt_dsp_init (int /*<<< orphan*/ *,struct sst_pdata*) ; 

__attribute__((used)) static int sst_byt_pcm_dev_probe(struct platform_device *pdev)
{
	struct sst_pdata *sst_pdata = dev_get_platdata(&pdev->dev);
	int ret;

	ret = sst_byt_dsp_init(&pdev->dev, sst_pdata);
	if (ret < 0)
		return -ENODEV;

	ret = devm_snd_soc_register_component(&pdev->dev, &byt_dai_component,
					 byt_dais, ARRAY_SIZE(byt_dais));
	if (ret < 0)
		goto err_plat;

	return 0;

err_plat:
	sst_byt_dsp_free(&pdev->dev, sst_pdata);
	return ret;
}