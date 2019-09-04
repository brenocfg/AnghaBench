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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,int) ; 

void odm_dynamic_tx_power_write_power_index(void *dm_void, u8 value)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 index;
	u32 power_index_reg[6] = {0xc90, 0xc91, 0xc92, 0xc98, 0xc99, 0xc9a};

	for (index = 0; index < 6; index++)
		odm_write_1byte(dm, power_index_reg[index], value);
}