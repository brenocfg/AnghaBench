#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct slot {struct hotplug_slot_ops* hotplug_slot; } ;
struct hotplug_slot_ops {struct hotplug_slot_ops* ops; struct slot* private; struct hotplug_slot_ops* info; int /*<<< orphan*/  set_attention_status; int /*<<< orphan*/  get_attention_status; int /*<<< orphan*/  get_latch_status; int /*<<< orphan*/  reset_slot; int /*<<< orphan*/  get_adapter_status; int /*<<< orphan*/  get_power_status; int /*<<< orphan*/  disable_slot; int /*<<< orphan*/  enable_slot; } ;
struct hotplug_slot_info {struct hotplug_slot_info* ops; struct slot* private; struct hotplug_slot_info* info; int /*<<< orphan*/  set_attention_status; int /*<<< orphan*/  get_attention_status; int /*<<< orphan*/  get_latch_status; int /*<<< orphan*/  reset_slot; int /*<<< orphan*/  get_adapter_status; int /*<<< orphan*/  get_power_status; int /*<<< orphan*/  disable_slot; int /*<<< orphan*/  enable_slot; } ;
struct hotplug_slot {struct hotplug_slot* ops; struct slot* private; struct hotplug_slot* info; int /*<<< orphan*/  set_attention_status; int /*<<< orphan*/  get_attention_status; int /*<<< orphan*/  get_latch_status; int /*<<< orphan*/  reset_slot; int /*<<< orphan*/  get_adapter_status; int /*<<< orphan*/  get_power_status; int /*<<< orphan*/  disable_slot; int /*<<< orphan*/  enable_slot; } ;
struct controller {TYPE_2__* pcie; struct slot* slot; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  subordinate; scalar_t__ hotplug_user_indicators; } ;

/* Variables and functions */
 scalar_t__ ATTN_LED (struct controller*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MRL_SENS (struct controller*) ; 
 int PSN (struct controller*) ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  disable_slot ; 
 int /*<<< orphan*/  enable_slot ; 
 int /*<<< orphan*/  get_adapter_status ; 
 int /*<<< orphan*/  get_attention_status ; 
 int /*<<< orphan*/  get_latch_status ; 
 int /*<<< orphan*/  get_power_status ; 
 int /*<<< orphan*/  kfree (struct hotplug_slot_ops*) ; 
 struct hotplug_slot_ops* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pci_hp_initialize (struct hotplug_slot_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pciehp_get_raw_indicator_status ; 
 int /*<<< orphan*/  pciehp_set_raw_indicator_status ; 
 int /*<<< orphan*/  reset_slot ; 
 int /*<<< orphan*/  set_attention_status ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int init_slot(struct controller *ctrl)
{
	struct slot *slot = ctrl->slot;
	struct hotplug_slot *hotplug = NULL;
	struct hotplug_slot_info *info = NULL;
	struct hotplug_slot_ops *ops = NULL;
	char name[SLOT_NAME_SIZE];
	int retval = -ENOMEM;

	hotplug = kzalloc(sizeof(*hotplug), GFP_KERNEL);
	if (!hotplug)
		goto out;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		goto out;

	/* Setup hotplug slot ops */
	ops = kzalloc(sizeof(*ops), GFP_KERNEL);
	if (!ops)
		goto out;

	ops->enable_slot = enable_slot;
	ops->disable_slot = disable_slot;
	ops->get_power_status = get_power_status;
	ops->get_adapter_status = get_adapter_status;
	ops->reset_slot = reset_slot;
	if (MRL_SENS(ctrl))
		ops->get_latch_status = get_latch_status;
	if (ATTN_LED(ctrl)) {
		ops->get_attention_status = get_attention_status;
		ops->set_attention_status = set_attention_status;
	} else if (ctrl->pcie->port->hotplug_user_indicators) {
		ops->get_attention_status = pciehp_get_raw_indicator_status;
		ops->set_attention_status = pciehp_set_raw_indicator_status;
	}

	/* register this slot with the hotplug pci core */
	hotplug->info = info;
	hotplug->private = slot;
	hotplug->ops = ops;
	slot->hotplug_slot = hotplug;
	snprintf(name, SLOT_NAME_SIZE, "%u", PSN(ctrl));

	retval = pci_hp_initialize(hotplug,
				   ctrl->pcie->port->subordinate, 0, name);
	if (retval)
		ctrl_err(ctrl, "pci_hp_initialize failed: error %d\n", retval);
out:
	if (retval) {
		kfree(ops);
		kfree(info);
		kfree(hotplug);
	}
	return retval;
}