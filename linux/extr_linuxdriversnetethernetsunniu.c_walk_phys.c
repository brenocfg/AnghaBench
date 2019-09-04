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
struct phy_probe_info {int dummy; } ;
struct niu_parent {scalar_t__ plat_type; int num_ports; int port_phy; struct phy_probe_info phy_probe_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  model; } ;
struct niu {int flags; int port; TYPE_1__ vpd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NIU_ALONSO_MDL_STR ; 
 int NIU_FLAGS_10G ; 
 int NIU_FLAGS_XCVR_SERDES ; 
 int /*<<< orphan*/  NIU_FOXXY_MDL_STR ; 
 int /*<<< orphan*/  NIU_KIMI_MDL_STR ; 
 scalar_t__ PLAT_TYPE_ATCA_CP3220 ; 
 scalar_t__ PLAT_TYPE_NIU ; 
 void* PLAT_TYPE_VF_P0 ; 
 void* PLAT_TYPE_VF_P1 ; 
 int /*<<< orphan*/  PORT_TYPE_10G ; 
 int /*<<< orphan*/  PORT_TYPE_1G ; 
 int count_10g_ports (struct phy_probe_info*,int*) ; 
 int count_1g_ports (struct phy_probe_info*,int*) ; 
 int fill_phy_probe_info (struct niu*,struct niu_parent*,struct phy_probe_info*) ; 
 int /*<<< orphan*/  niu_divide_channels (struct niu_parent*,int,int) ; 
 int /*<<< orphan*/  niu_divide_rdc_groups (struct niu_parent*,int,int) ; 
 int /*<<< orphan*/  niu_n2_divide_channels (struct niu_parent*) ; 
 int phy_encode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int walk_phys(struct niu *np, struct niu_parent *parent)
{
	struct phy_probe_info *info = &parent->phy_probe_info;
	int lowest_10g, lowest_1g;
	int num_10g, num_1g;
	u32 val;
	int err;

	num_10g = num_1g = 0;

	if (!strcmp(np->vpd.model, NIU_ALONSO_MDL_STR) ||
	    !strcmp(np->vpd.model, NIU_KIMI_MDL_STR)) {
		num_10g = 0;
		num_1g = 2;
		parent->plat_type = PLAT_TYPE_ATCA_CP3220;
		parent->num_ports = 4;
		val = (phy_encode(PORT_TYPE_1G, 0) |
		       phy_encode(PORT_TYPE_1G, 1) |
		       phy_encode(PORT_TYPE_1G, 2) |
		       phy_encode(PORT_TYPE_1G, 3));
	} else if (!strcmp(np->vpd.model, NIU_FOXXY_MDL_STR)) {
		num_10g = 2;
		num_1g = 0;
		parent->num_ports = 2;
		val = (phy_encode(PORT_TYPE_10G, 0) |
		       phy_encode(PORT_TYPE_10G, 1));
	} else if ((np->flags & NIU_FLAGS_XCVR_SERDES) &&
		   (parent->plat_type == PLAT_TYPE_NIU)) {
		/* this is the Monza case */
		if (np->flags & NIU_FLAGS_10G) {
			val = (phy_encode(PORT_TYPE_10G, 0) |
			       phy_encode(PORT_TYPE_10G, 1));
		} else {
			val = (phy_encode(PORT_TYPE_1G, 0) |
			       phy_encode(PORT_TYPE_1G, 1));
		}
	} else {
		err = fill_phy_probe_info(np, parent, info);
		if (err)
			return err;

		num_10g = count_10g_ports(info, &lowest_10g);
		num_1g = count_1g_ports(info, &lowest_1g);

		switch ((num_10g << 4) | num_1g) {
		case 0x24:
			if (lowest_1g == 10)
				parent->plat_type = PLAT_TYPE_VF_P0;
			else if (lowest_1g == 26)
				parent->plat_type = PLAT_TYPE_VF_P1;
			else
				goto unknown_vg_1g_port;

			/* fallthru */
		case 0x22:
			val = (phy_encode(PORT_TYPE_10G, 0) |
			       phy_encode(PORT_TYPE_10G, 1) |
			       phy_encode(PORT_TYPE_1G, 2) |
			       phy_encode(PORT_TYPE_1G, 3));
			break;

		case 0x20:
			val = (phy_encode(PORT_TYPE_10G, 0) |
			       phy_encode(PORT_TYPE_10G, 1));
			break;

		case 0x10:
			val = phy_encode(PORT_TYPE_10G, np->port);
			break;

		case 0x14:
			if (lowest_1g == 10)
				parent->plat_type = PLAT_TYPE_VF_P0;
			else if (lowest_1g == 26)
				parent->plat_type = PLAT_TYPE_VF_P1;
			else
				goto unknown_vg_1g_port;

			/* fallthru */
		case 0x13:
			if ((lowest_10g & 0x7) == 0)
				val = (phy_encode(PORT_TYPE_10G, 0) |
				       phy_encode(PORT_TYPE_1G, 1) |
				       phy_encode(PORT_TYPE_1G, 2) |
				       phy_encode(PORT_TYPE_1G, 3));
			else
				val = (phy_encode(PORT_TYPE_1G, 0) |
				       phy_encode(PORT_TYPE_10G, 1) |
				       phy_encode(PORT_TYPE_1G, 2) |
				       phy_encode(PORT_TYPE_1G, 3));
			break;

		case 0x04:
			if (lowest_1g == 10)
				parent->plat_type = PLAT_TYPE_VF_P0;
			else if (lowest_1g == 26)
				parent->plat_type = PLAT_TYPE_VF_P1;
			else
				goto unknown_vg_1g_port;

			val = (phy_encode(PORT_TYPE_1G, 0) |
			       phy_encode(PORT_TYPE_1G, 1) |
			       phy_encode(PORT_TYPE_1G, 2) |
			       phy_encode(PORT_TYPE_1G, 3));
			break;

		default:
			pr_err("Unsupported port config 10G[%d] 1G[%d]\n",
			       num_10g, num_1g);
			return -EINVAL;
		}
	}

	parent->port_phy = val;

	if (parent->plat_type == PLAT_TYPE_NIU)
		niu_n2_divide_channels(parent);
	else
		niu_divide_channels(parent, num_10g, num_1g);

	niu_divide_rdc_groups(parent, num_10g, num_1g);

	return 0;

unknown_vg_1g_port:
	pr_err("Cannot identify platform type, 1gport=%d\n", lowest_1g);
	return -EINVAL;
}