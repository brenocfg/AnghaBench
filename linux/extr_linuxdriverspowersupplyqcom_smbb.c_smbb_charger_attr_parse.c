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
struct smbb_charger_attr {int /*<<< orphan*/  fail_ok; int /*<<< orphan*/  name; } ;
struct smbb_charger {TYPE_1__* dev; } ;
typedef  enum smbb_attr { ____Placeholder_smbb_attr } smbb_attr ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int of_property_read_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int smbb_charger_attr_read (struct smbb_charger*,int) ; 
 int smbb_charger_attr_write (struct smbb_charger*,int,unsigned int) ; 
 struct smbb_charger_attr* smbb_charger_attrs ; 

__attribute__((used)) static int smbb_charger_attr_parse(struct smbb_charger *chg,
		enum smbb_attr which)
{
	const struct smbb_charger_attr *prop;
	unsigned int val;
	int rc;

	prop = &smbb_charger_attrs[which];

	rc = of_property_read_u32(chg->dev->of_node, prop->name, &val);
	if (rc == 0) {
		rc = smbb_charger_attr_write(chg, which, val);
		if (!rc || !prop->fail_ok)
			return rc;
	}
	return smbb_charger_attr_read(chg, which);
}