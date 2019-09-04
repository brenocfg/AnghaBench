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
typedef  int u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct fsl_elbc_gpcm {scalar_t__ bank; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BR_BA ; 
 int BR_MSEL ; 
 int BR_MS_GPCM ; 
 int ENODEV ; 
 scalar_t__ MAX_BANKS ; 
 int OR_GPCM_AM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fsl_lbc_addr (int /*<<< orphan*/ ) ; 
 int resource_size (struct resource*) ; 

__attribute__((used)) static int check_of_data(struct fsl_elbc_gpcm *priv,
				   struct resource *res,
				   u32 reg_br, u32 reg_or)
{
	/* check specified bank */
	if (priv->bank >= MAX_BANKS) {
		dev_err(priv->dev, "invalid bank\n");
		return -ENODEV;
	}

	/* check specified mode (BR_MS_GPCM is 0) */
	if ((reg_br & BR_MSEL) != BR_MS_GPCM) {
		dev_err(priv->dev, "unsupported mode\n");
		return -ENODEV;
	}

	/* check specified mask vs. resource size */
	if ((~(reg_or & OR_GPCM_AM) + 1) != resource_size(res)) {
		dev_err(priv->dev, "address mask / size mismatch\n");
		return -ENODEV;
	}

	/* check specified address */
	if ((reg_br & reg_or & BR_BA) != fsl_lbc_addr(res->start)) {
		dev_err(priv->dev, "base address mismatch\n");
		return -ENODEV;
	}

	return 0;
}