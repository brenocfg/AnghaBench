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
typedef  scalar_t__ u32 ;
struct ipw2100_ordinals {scalar_t__ table1_addr; } ;
struct ipw2100_priv {int /*<<< orphan*/  net_dev; struct ipw2100_ordinals ordinals; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 scalar_t__ IPW_ORD_TAB_1_ENTRY_SIZE ; 
 scalar_t__ IS_ORDINAL_TABLE_ONE (struct ipw2100_ordinals*,scalar_t__) ; 
 scalar_t__ IS_ORDINAL_TABLE_TWO (struct ipw2100_ordinals*,scalar_t__) ; 
 int /*<<< orphan*/  read_nic_dword (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  write_nic_dword (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ipw2100_set_ordinal(struct ipw2100_priv *priv, u32 ord, u32 * val,
			       u32 * len)
{
	struct ipw2100_ordinals *ordinals = &priv->ordinals;
	u32 addr;

	if (IS_ORDINAL_TABLE_ONE(ordinals, ord)) {
		if (*len != IPW_ORD_TAB_1_ENTRY_SIZE) {
			*len = IPW_ORD_TAB_1_ENTRY_SIZE;
			IPW_DEBUG_INFO("wrong size\n");
			return -EINVAL;
		}

		read_nic_dword(priv->net_dev,
			       ordinals->table1_addr + (ord << 2), &addr);

		write_nic_dword(priv->net_dev, addr, *val);

		*len = IPW_ORD_TAB_1_ENTRY_SIZE;

		return 0;
	}

	IPW_DEBUG_INFO("wrong table\n");
	if (IS_ORDINAL_TABLE_TWO(ordinals, ord))
		return -EINVAL;

	return -EINVAL;
}