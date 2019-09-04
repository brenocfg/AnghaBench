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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_ssi {int /*<<< orphan*/  ac97_reg_lock; TYPE_1__* soc; scalar_t__ card_pdev; int /*<<< orphan*/  dbg_stats; } ;
struct TYPE_2__ {scalar_t__ imx; } ;

/* Variables and functions */
 struct fsl_ssi* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_ssi_debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_ssi_hw_clean (struct fsl_ssi*) ; 
 int /*<<< orphan*/  fsl_ssi_imx_clean (struct platform_device*,struct fsl_ssi*) ; 
 scalar_t__ fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_ssi_remove(struct platform_device *pdev)
{
	struct fsl_ssi *ssi = dev_get_drvdata(&pdev->dev);

	fsl_ssi_debugfs_remove(&ssi->dbg_stats);

	if (ssi->card_pdev)
		platform_device_unregister(ssi->card_pdev);

	/* Clean up SSI registers */
	fsl_ssi_hw_clean(ssi);

	if (ssi->soc->imx)
		fsl_ssi_imx_clean(pdev, ssi);

	if (fsl_ssi_is_ac97(ssi)) {
		snd_soc_set_ac97_ops(NULL);
		mutex_destroy(&ssi->ac97_reg_lock);
	}

	return 0;
}