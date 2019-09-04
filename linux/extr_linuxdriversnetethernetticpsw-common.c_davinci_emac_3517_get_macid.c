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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_MAC_HI_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTRL_MAC_LO_REG (int /*<<< orphan*/ ,int) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int davinci_emac_3517_get_macid(struct device *dev, u16 offset,
				       int slave, u8 *mac_addr)
{
	u32 macid_lsb;
	u32 macid_msb;
	struct regmap *syscon;

	syscon = syscon_regmap_lookup_by_phandle(dev->of_node, "syscon");
	if (IS_ERR(syscon)) {
		if (PTR_ERR(syscon) == -ENODEV)
			return 0;
		return PTR_ERR(syscon);
	}

	regmap_read(syscon, CTRL_MAC_LO_REG(offset, slave), &macid_lsb);
	regmap_read(syscon, CTRL_MAC_HI_REG(offset, slave), &macid_msb);

	mac_addr[0] = (macid_msb >> 16) & 0xff;
	mac_addr[1] = (macid_msb >> 8)  & 0xff;
	mac_addr[2] = macid_msb & 0xff;
	mac_addr[3] = (macid_lsb >> 16) & 0xff;
	mac_addr[4] = (macid_lsb >> 8)  & 0xff;
	mac_addr[5] = macid_lsb & 0xff;

	return 0;
}