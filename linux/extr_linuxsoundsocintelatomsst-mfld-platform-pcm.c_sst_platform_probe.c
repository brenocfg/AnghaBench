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
struct sst_platform_data {int /*<<< orphan*/  strm_map_size; int /*<<< orphan*/  pdev_strm_map; } ;
struct sst_data {int /*<<< orphan*/  lock; struct platform_device* pdev; struct sst_platform_data* pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct sst_data*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpcm_strm_map ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_platform_dai ; 
 int /*<<< orphan*/  sst_soc_platform_drv ; 

__attribute__((used)) static int sst_platform_probe(struct platform_device *pdev)
{
	struct sst_data *drv;
	int ret;
	struct sst_platform_data *pdata;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (drv == NULL) {
		return -ENOMEM;
	}

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (pdata == NULL) {
		return -ENOMEM;
	}

	pdata->pdev_strm_map = dpcm_strm_map;
	pdata->strm_map_size = ARRAY_SIZE(dpcm_strm_map);
	drv->pdata = pdata;
	drv->pdev = pdev;
	mutex_init(&drv->lock);
	dev_set_drvdata(&pdev->dev, drv);

	ret = devm_snd_soc_register_component(&pdev->dev, &sst_soc_platform_drv,
				sst_platform_dai, ARRAY_SIZE(sst_platform_dai));
	if (ret)
		dev_err(&pdev->dev, "registering cpu dais failed\n");

	return ret;
}