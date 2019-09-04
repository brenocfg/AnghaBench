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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phydm_dynamic_switch_htstf_mumimo_8822b (struct phy_dm_struct*) ; 

void phydm_hwsetting_8822b(struct phy_dm_struct *dm)
{
	phydm_dynamic_switch_htstf_mumimo_8822b(dm);
}