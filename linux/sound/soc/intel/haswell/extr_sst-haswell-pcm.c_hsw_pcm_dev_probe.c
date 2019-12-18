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
struct sst_pdata {int /*<<< orphan*/  dsp; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hsw_priv_data {int /*<<< orphan*/  hsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sst_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct hsw_priv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsw_dai_component ; 
 int /*<<< orphan*/  hsw_dais ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hsw_priv_data*) ; 
 int /*<<< orphan*/  sst_hsw_dsp_free (int /*<<< orphan*/ *,struct sst_pdata*) ; 
 int sst_hsw_dsp_init (int /*<<< orphan*/ *,struct sst_pdata*) ; 

__attribute__((used)) static int hsw_pcm_dev_probe(struct platform_device *pdev)
{
	struct sst_pdata *sst_pdata = dev_get_platdata(&pdev->dev);
	struct hsw_priv_data *priv_data;
	int ret;

	if (!sst_pdata)
		return -EINVAL;

	priv_data = devm_kzalloc(&pdev->dev, sizeof(*priv_data), GFP_KERNEL);
	if (!priv_data)
		return -ENOMEM;

	ret = sst_hsw_dsp_init(&pdev->dev, sst_pdata);
	if (ret < 0)
		return -ENODEV;

	priv_data->hsw = sst_pdata->dsp;
	platform_set_drvdata(pdev, priv_data);

	ret = devm_snd_soc_register_component(&pdev->dev, &hsw_dai_component,
		hsw_dais, ARRAY_SIZE(hsw_dais));
	if (ret < 0)
		goto err_plat;

	return 0;

err_plat:
	sst_hsw_dsp_free(&pdev->dev, sst_pdata);
	return 0;
}