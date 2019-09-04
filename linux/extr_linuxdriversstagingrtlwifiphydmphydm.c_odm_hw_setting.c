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
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  phydm_hwsetting_8822b (struct phy_dm_struct*) ; 

__attribute__((used)) static void odm_hw_setting(struct phy_dm_struct *dm)
{
	if (dm->support_ic_type & ODM_RTL8822B)
		phydm_hwsetting_8822b(dm);
}