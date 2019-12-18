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
struct fsl_esai {int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;

/* Variables and functions */
 int ESAI_ECR_ERST ; 
 int ESAI_ECR_ERST_MASK ; 
 int ESAI_ECR_ESAIEN ; 
 int ESAI_ECR_ESAIEN_MASK ; 
 int ESAI_PCRC_PC_MASK ; 
 int ESAI_PRRC_PDC_MASK ; 
 int /*<<< orphan*/  REG_ESAI_ECR ; 
 int /*<<< orphan*/  REG_ESAI_PCRC ; 
 int /*<<< orphan*/  REG_ESAI_PRRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int fsl_esai_hw_init(struct fsl_esai *esai_priv)
{
	struct platform_device *pdev = esai_priv->pdev;
	int ret;

	/* Reset ESAI unit */
	ret = regmap_update_bits(esai_priv->regmap, REG_ESAI_ECR,
				 ESAI_ECR_ESAIEN_MASK | ESAI_ECR_ERST_MASK,
				 ESAI_ECR_ESAIEN | ESAI_ECR_ERST);
	if (ret) {
		dev_err(&pdev->dev, "failed to reset ESAI: %d\n", ret);
		return ret;
	}

	/*
	 * We need to enable ESAI so as to access some of its registers.
	 * Otherwise, we would fail to dump regmap from user space.
	 */
	ret = regmap_update_bits(esai_priv->regmap, REG_ESAI_ECR,
				 ESAI_ECR_ESAIEN_MASK | ESAI_ECR_ERST_MASK,
				 ESAI_ECR_ESAIEN);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable ESAI: %d\n", ret);
		return ret;
	}

	regmap_update_bits(esai_priv->regmap, REG_ESAI_PRRC,
			   ESAI_PRRC_PDC_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PCRC,
			   ESAI_PCRC_PC_MASK, 0);

	return 0;
}