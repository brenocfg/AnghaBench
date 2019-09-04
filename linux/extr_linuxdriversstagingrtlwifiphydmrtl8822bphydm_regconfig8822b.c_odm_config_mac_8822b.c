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
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void odm_config_mac_8822b(struct phy_dm_struct *dm, u32 addr, u8 data)
{
	odm_write_1byte(dm, addr, data);
	ODM_RT_TRACE(
		dm, ODM_COMP_INIT,
		"===> odm_config_mac_with_header_file: [MAC_REG] %08X %08X\n",
		addr, data);
}