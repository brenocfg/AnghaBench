#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {char* name; TYPE_7__** attrs; } ;
struct TYPE_14__ {char* name; int mode; } ;
struct TYPE_10__ {int /*<<< orphan*/  store; int /*<<< orphan*/  show; TYPE_7__ attr; } ;
struct TYPE_9__ {int /*<<< orphan*/  show; TYPE_7__ attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  show; TYPE_7__ attr; } ;
struct charger_regulator {int /*<<< orphan*/  regulator_name; TYPE_6__ attr_g; int /*<<< orphan*/  externally_control; TYPE_3__ attr_externally_control; TYPE_2__ attr_state; TYPE_1__ attr_name; TYPE_7__** attrs; } ;
struct charger_manager {int /*<<< orphan*/  dev; TYPE_5__* charger_psy; struct charger_desc* desc; } ;
struct charger_desc {int num_charger_regulators; struct charger_regulator* charger_regulators; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_12__ {TYPE_4__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  charger_externally_control_show ; 
 int /*<<< orphan*/  charger_externally_control_store ; 
 int /*<<< orphan*/  charger_name_show ; 
 int /*<<< orphan*/  charger_state_show ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* devm_kzalloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_7__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_6__*) ; 

__attribute__((used)) static int charger_manager_register_sysfs(struct charger_manager *cm)
{
	struct charger_desc *desc = cm->desc;
	struct charger_regulator *charger;
	int chargers_externally_control = 1;
	char buf[11];
	char *str;
	int ret;
	int i;

	/* Create sysfs entry to control charger(regulator) */
	for (i = 0; i < desc->num_charger_regulators; i++) {
		charger = &desc->charger_regulators[i];

		snprintf(buf, 10, "charger.%d", i);
		str = devm_kzalloc(cm->dev,
				strlen(buf) + 1, GFP_KERNEL);
		if (!str)
			return -ENOMEM;

		strcpy(str, buf);

		charger->attrs[0] = &charger->attr_name.attr;
		charger->attrs[1] = &charger->attr_state.attr;
		charger->attrs[2] = &charger->attr_externally_control.attr;
		charger->attrs[3] = NULL;
		charger->attr_g.name = str;
		charger->attr_g.attrs = charger->attrs;

		sysfs_attr_init(&charger->attr_name.attr);
		charger->attr_name.attr.name = "name";
		charger->attr_name.attr.mode = 0444;
		charger->attr_name.show = charger_name_show;

		sysfs_attr_init(&charger->attr_state.attr);
		charger->attr_state.attr.name = "state";
		charger->attr_state.attr.mode = 0444;
		charger->attr_state.show = charger_state_show;

		sysfs_attr_init(&charger->attr_externally_control.attr);
		charger->attr_externally_control.attr.name
				= "externally_control";
		charger->attr_externally_control.attr.mode = 0644;
		charger->attr_externally_control.show
				= charger_externally_control_show;
		charger->attr_externally_control.store
				= charger_externally_control_store;

		if (!desc->charger_regulators[i].externally_control ||
				!chargers_externally_control)
			chargers_externally_control = 0;

		dev_info(cm->dev, "'%s' regulator's externally_control is %d\n",
			 charger->regulator_name, charger->externally_control);

		ret = sysfs_create_group(&cm->charger_psy->dev.kobj,
					&charger->attr_g);
		if (ret < 0) {
			dev_err(cm->dev, "Cannot create sysfs entry of %s regulator\n",
				charger->regulator_name);
			return ret;
		}
	}

	if (chargers_externally_control) {
		dev_err(cm->dev, "Cannot register regulator because charger-manager must need at least one charger for charging battery\n");
		return -EINVAL;
	}

	return 0;
}