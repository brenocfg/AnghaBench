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
struct regmap {int dummy; } ;
struct fsl_spdif_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SPDIF_SIC ; 
 int /*<<< orphan*/  REG_SPDIF_SIE ; 
 int /*<<< orphan*/  REG_SPDIF_SIS ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 spdif_intr_status_clear(struct fsl_spdif_priv *spdif_priv)
{
	struct regmap *regmap = spdif_priv->regmap;
	u32 val, val2;

	regmap_read(regmap, REG_SPDIF_SIS, &val);
	regmap_read(regmap, REG_SPDIF_SIE, &val2);

	regmap_write(regmap, REG_SPDIF_SIC, val & val2);

	return val;
}