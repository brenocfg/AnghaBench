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
 int /*<<< orphan*/  _iqk_bb_reset_8822b (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_afe_setting_8822b(struct phy_dm_struct *dm, bool do_iqk)
{
	if (do_iqk) {
		odm_write_4byte(dm, 0xc60, 0x50000000);
		odm_write_4byte(dm, 0xc60, 0x70070040);
		odm_write_4byte(dm, 0xe60, 0x50000000);
		odm_write_4byte(dm, 0xe60, 0x70070040);

		odm_write_4byte(dm, 0xc58, 0xd8000402);
		odm_write_4byte(dm, 0xc5c, 0xd1000120);
		odm_write_4byte(dm, 0xc6c, 0x00000a15);
		odm_write_4byte(dm, 0xe58, 0xd8000402);
		odm_write_4byte(dm, 0xe5c, 0xd1000120);
		odm_write_4byte(dm, 0xe6c, 0x00000a15);
		_iqk_bb_reset_8822b(dm);
	} else {
		odm_write_4byte(dm, 0xc60, 0x50000000);
		odm_write_4byte(dm, 0xc60, 0x70038040);
		odm_write_4byte(dm, 0xe60, 0x50000000);
		odm_write_4byte(dm, 0xe60, 0x70038040);

		odm_write_4byte(dm, 0xc58, 0xd8020402);
		odm_write_4byte(dm, 0xc5c, 0xde000120);
		odm_write_4byte(dm, 0xc6c, 0x0000122a);
		odm_write_4byte(dm, 0xe58, 0xd8020402);
		odm_write_4byte(dm, 0xe5c, 0xde000120);
		odm_write_4byte(dm, 0xe6c, 0x0000122a);
	}
}