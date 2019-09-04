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
typedef  int u32 ;
struct cpsw_ale_params {int ale_ageout; int major_ver_mask; int ale_entries; int /*<<< orphan*/  ale_ports; scalar_t__ nu_switch_ale; int /*<<< orphan*/  dev; scalar_t__ ale_regs; } ;
struct cpsw_ale {int ageout; int version; struct cpsw_ale_params params; int /*<<< orphan*/  vlan_field_bits; int /*<<< orphan*/  port_num_bits; int /*<<< orphan*/  port_mask_bits; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; scalar_t__ shift; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 scalar_t__ ALE_IDVER ; 
 size_t ALE_PORT_UNKNOWN_MCAST_FLOOD ; 
 size_t ALE_PORT_UNKNOWN_REG_MCAST_FLOOD ; 
 size_t ALE_PORT_UNKNOWN_VLAN_MEMBER ; 
 size_t ALE_PORT_UNTAGGED_EGRESS ; 
 scalar_t__ ALE_STATUS ; 
 int ALE_STATUS_SIZE_MASK ; 
 int ALE_TABLE_SIZE_DEFAULT ; 
 int ALE_TABLE_SIZE_MULTIPLIER ; 
 int /*<<< orphan*/  ALE_UNKNOWNVLAN_FORCE_UNTAG_EGRESS ; 
 int /*<<< orphan*/  ALE_UNKNOWNVLAN_MEMBER ; 
 int /*<<< orphan*/  ALE_UNKNOWNVLAN_REG_MCAST_FLOOD ; 
 int /*<<< orphan*/  ALE_UNKNOWNVLAN_UNREG_MCAST_FLOOD ; 
 int ALE_VERSION_MAJOR (int,int) ; 
 int ALE_VERSION_MINOR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 TYPE_1__* ale_controls ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 struct cpsw_ale* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_base_2 (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 

struct cpsw_ale *cpsw_ale_create(struct cpsw_ale_params *params)
{
	struct cpsw_ale *ale;
	u32 rev, ale_entries;

	ale = devm_kzalloc(params->dev, sizeof(*ale), GFP_KERNEL);
	if (!ale)
		return NULL;

	ale->params = *params;
	ale->ageout = ale->params.ale_ageout * HZ;

	rev = readl_relaxed(ale->params.ale_regs + ALE_IDVER);
	if (!ale->params.major_ver_mask)
		ale->params.major_ver_mask = 0xff;
	ale->version =
		(ALE_VERSION_MAJOR(rev, ale->params.major_ver_mask) << 8) |
		 ALE_VERSION_MINOR(rev);
	dev_info(ale->params.dev, "initialized cpsw ale version %d.%d\n",
		 ALE_VERSION_MAJOR(rev, ale->params.major_ver_mask),
		 ALE_VERSION_MINOR(rev));

	if (!ale->params.ale_entries) {
		ale_entries =
			readl_relaxed(ale->params.ale_regs + ALE_STATUS) &
			ALE_STATUS_SIZE_MASK;
		/* ALE available on newer NetCP switches has introduced
		 * a register, ALE_STATUS, to indicate the size of ALE
		 * table which shows the size as a multiple of 1024 entries.
		 * For these, params.ale_entries will be set to zero. So
		 * read the register and update the value of ale_entries.
		 * ALE table on NetCP lite, is much smaller and is indicated
		 * by a value of zero in ALE_STATUS. So use a default value
		 * of ALE_TABLE_SIZE_DEFAULT for this. Caller is expected
		 * to set the value of ale_entries for all other versions
		 * of ALE.
		 */
		if (!ale_entries)
			ale_entries = ALE_TABLE_SIZE_DEFAULT;
		else
			ale_entries *= ALE_TABLE_SIZE_MULTIPLIER;
		ale->params.ale_entries = ale_entries;
	}
	dev_info(ale->params.dev,
		 "ALE Table size %ld\n", ale->params.ale_entries);

	/* set default bits for existing h/w */
	ale->port_mask_bits = ale->params.ale_ports;
	ale->port_num_bits = order_base_2(ale->params.ale_ports);
	ale->vlan_field_bits = ale->params.ale_ports;

	/* Set defaults override for ALE on NetCP NU switch and for version
	 * 1R3
	 */
	if (ale->params.nu_switch_ale) {
		/* Separate registers for unknown vlan configuration.
		 * Also there are N bits, where N is number of ale
		 * ports and shift value should be 0
		 */
		ale_controls[ALE_PORT_UNKNOWN_VLAN_MEMBER].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNKNOWN_VLAN_MEMBER].offset =
					ALE_UNKNOWNVLAN_MEMBER;
		ale_controls[ALE_PORT_UNKNOWN_MCAST_FLOOD].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNKNOWN_MCAST_FLOOD].shift = 0;
		ale_controls[ALE_PORT_UNKNOWN_MCAST_FLOOD].offset =
					ALE_UNKNOWNVLAN_UNREG_MCAST_FLOOD;
		ale_controls[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD].shift = 0;
		ale_controls[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD].offset =
					ALE_UNKNOWNVLAN_REG_MCAST_FLOOD;
		ale_controls[ALE_PORT_UNTAGGED_EGRESS].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNTAGGED_EGRESS].shift = 0;
		ale_controls[ALE_PORT_UNTAGGED_EGRESS].offset =
					ALE_UNKNOWNVLAN_FORCE_UNTAG_EGRESS;
	}

	return ale;
}