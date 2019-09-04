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
typedef  int /*<<< orphan*/  u8 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int ODM_RTL8814A ; 
 int /*<<< orphan*/  phydm_set_kfree_to_rf_8814a (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_set_kfree_to_rf(void *dm_void, u8 e_rf_path, u8 data)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_RTL8814A)
		phydm_set_kfree_to_rf_8814a(dm, e_rf_path, data);
}