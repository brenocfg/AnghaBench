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
struct phy_dm_struct {int fw_buff_is_enpty; scalar_t__ pre_c2h_seq; scalar_t__ debug_components; scalar_t__ fw_debug_components; int /*<<< orphan*/  debug_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_DBG_TRACE ; 

void phydm_init_debug_setting(struct phy_dm_struct *dm)
{
	dm->debug_level = ODM_DBG_TRACE;

	dm->fw_debug_components = 0;
	dm->debug_components =

		0;

	dm->fw_buff_is_enpty = true;
	dm->pre_c2h_seq = 0;
}