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
typedef  int /*<<< orphan*/  u32 ;
struct rtl8366_smi {TYPE_1__* parent; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL8366RB_PORT_ALL ; 
 int /*<<< orphan*/  RTL8366RB_SGCR ; 
 int /*<<< orphan*/  RTL8366RB_SGCR_MAX_LENGTH_1536 ; 
 int /*<<< orphan*/  RTL8366RB_SGCR_MAX_LENGTH_MASK ; 
 int /*<<< orphan*/  RTL8366RB_SSCR0 ; 
 int /*<<< orphan*/  RTL8366RB_SSCR1 ; 
 int /*<<< orphan*/  RTL8366RB_SSCR2 ; 
 int /*<<< orphan*/  RTL8366RB_SSCR2_DROP_UNKNOWN_DA ; 
 int /*<<< orphan*/  RTL8366RB_VLAN_INGRESS_CTRL2_REG ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,unsigned int*) ; 

__attribute__((used)) static int rtl8366rb_setup(struct rtl8366_smi *smi)
{
	int err;
#ifdef CONFIG_OF
	unsigned i;
	struct device_node *np;
	unsigned num_initvals;
	const __be32 *paddr;

	np = smi->parent->of_node;

	paddr = of_get_property(np, "realtek,initvals", &num_initvals);
	if (paddr) {
		dev_info(smi->parent, "applying initvals from DTS\n");

		if (num_initvals < (2 * sizeof(*paddr)))
			return -EINVAL;

		num_initvals /= sizeof(*paddr);

		for (i = 0; i < num_initvals - 1; i += 2) {
			u32 reg = be32_to_cpup(paddr + i);
			u32 val = be32_to_cpup(paddr + i + 1);

			REG_WR(smi, reg, val);
		}
	}
#endif

	/* set maximum packet length to 1536 bytes */
	REG_RMW(smi, RTL8366RB_SGCR, RTL8366RB_SGCR_MAX_LENGTH_MASK,
		RTL8366RB_SGCR_MAX_LENGTH_1536);

	/* enable learning for all ports */
	REG_WR(smi, RTL8366RB_SSCR0, 0);

	/* enable auto ageing for all ports */
	REG_WR(smi, RTL8366RB_SSCR1, 0);

	/*
	 * discard VLAN tagged packets if the port is not a member of
	 * the VLAN with which the packets is associated.
	 */
	REG_WR(smi, RTL8366RB_VLAN_INGRESS_CTRL2_REG, RTL8366RB_PORT_ALL);

	/* don't drop packets whose DA has not been learned */
	REG_RMW(smi, RTL8366RB_SSCR2, RTL8366RB_SSCR2_DROP_UNKNOWN_DA, 0);

	return 0;
}