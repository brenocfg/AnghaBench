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
struct snvs_lpgpr_priv {int /*<<< orphan*/  regmap; struct snvs_lpgpr_cfg* dcfg; } ;
struct snvs_lpgpr_cfg {scalar_t__ offset; int /*<<< orphan*/  offset_lplr; int /*<<< orphan*/  offset_hplr; } ;

/* Variables and functions */
 int EPERM ; 
 unsigned int IMX_GPR_HL ; 
 unsigned int IMX_GPR_SL ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,scalar_t__,void*,size_t) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int snvs_lpgpr_write(void *context, unsigned int offset, void *val,
			    size_t bytes)
{
	struct snvs_lpgpr_priv *priv = context;
	const struct snvs_lpgpr_cfg *dcfg = priv->dcfg;
	unsigned int lock_reg;
	int ret;

	ret = regmap_read(priv->regmap, dcfg->offset_hplr, &lock_reg);
	if (ret < 0)
		return ret;

	if (lock_reg & IMX_GPR_SL)
		return -EPERM;

	ret = regmap_read(priv->regmap, dcfg->offset_lplr, &lock_reg);
	if (ret < 0)
		return ret;

	if (lock_reg & IMX_GPR_HL)
		return -EPERM;

	return regmap_bulk_write(priv->regmap, dcfg->offset + offset, val,
				bytes / 4);
}