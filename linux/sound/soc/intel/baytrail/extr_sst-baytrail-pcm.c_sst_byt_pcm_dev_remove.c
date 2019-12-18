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
 struct sst_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_byt_dsp_free (int /*<<< orphan*/ *,struct sst_pdata*) ; 

__attribute__((used)) static int sst_byt_pcm_dev_remove(struct platform_device *pdev)
{
	struct sst_pdata *sst_pdata = dev_get_platdata(&pdev->dev);

	sst_byt_dsp_free(&pdev->dev, sst_pdata);

	return 0;
}