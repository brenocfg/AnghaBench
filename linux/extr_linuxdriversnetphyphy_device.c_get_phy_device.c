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
struct phy_device {int dummy; } ;
struct phy_c45_device_ids {int /*<<< orphan*/  member_0; } ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct phy_device* ERR_PTR (int) ; 
 int get_phy_id (struct mii_bus*,int,int*,int,struct phy_c45_device_ids*) ; 
 struct phy_device* phy_device_create (struct mii_bus*,int,int,int,struct phy_c45_device_ids*) ; 

struct phy_device *get_phy_device(struct mii_bus *bus, int addr, bool is_c45)
{
	struct phy_c45_device_ids c45_ids = {0};
	u32 phy_id = 0;
	int r;

	r = get_phy_id(bus, addr, &phy_id, is_c45, &c45_ids);
	if (r)
		return ERR_PTR(r);

	/* If the phy_id is mostly Fs, there is no device there */
	if ((phy_id & 0x1fffffff) == 0x1fffffff)
		return ERR_PTR(-ENODEV);

	return phy_device_create(bus, addr, phy_id, is_c45, &c45_ids);
}