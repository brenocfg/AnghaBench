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
struct smbb_charger_attr {unsigned int (* hw_fn ) (unsigned int) ;int /*<<< orphan*/  name; scalar_t__ reg; } ;
struct smbb_charger {unsigned int* attr; int /*<<< orphan*/  dev; scalar_t__ addr; int /*<<< orphan*/  regmap; } ;
typedef  enum smbb_attr { ____Placeholder_smbb_attr } smbb_attr ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 struct smbb_charger_attr* smbb_charger_attrs ; 
 unsigned int stub1 (unsigned int) ; 

__attribute__((used)) static int smbb_charger_attr_read(struct smbb_charger *chg,
		enum smbb_attr which)
{
	const struct smbb_charger_attr *prop;
	unsigned int val;
	int rc;

	prop = &smbb_charger_attrs[which];

	rc = regmap_read(chg->regmap, chg->addr + prop->reg, &val);
	if (rc) {
		dev_err(chg->dev, "failed to read %s\n", prop->name);
		return rc;
	}
	val = prop->hw_fn(val);
	dev_dbg(chg->dev, "%s => %d\n", prop->name, val);

	chg->attr[which] = val;

	return 0;
}