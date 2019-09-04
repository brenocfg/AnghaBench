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
typedef  size_t u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 size_t BB_REG_NUM_8822B ; 
 size_t MAC_REG_NUM_8822B ; 
 size_t odm_read_4byte (struct phy_dm_struct*,size_t) ; 

__attribute__((used)) static void _iqk_backup_mac_bb_8822b(struct phy_dm_struct *dm, u32 *MAC_backup,
				     u32 *BB_backup, u32 *backup_mac_reg,
				     u32 *backup_bb_reg)
{
	u32 i;

	for (i = 0; i < MAC_REG_NUM_8822B; i++)
		MAC_backup[i] = odm_read_4byte(dm, backup_mac_reg[i]);

	for (i = 0; i < BB_REG_NUM_8822B; i++)
		BB_backup[i] = odm_read_4byte(dm, backup_bb_reg[i]);
}