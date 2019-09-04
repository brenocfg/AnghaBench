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
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_rfe_setting_8822b(struct phy_dm_struct *dm, bool ext_pa_on)
{
	if (ext_pa_on) {
		/*RFE setting*/
		odm_write_4byte(dm, 0xcb0, 0x77777777);
		odm_write_4byte(dm, 0xcb4, 0x00007777);
		odm_write_4byte(dm, 0xcbc, 0x0000083B);
		odm_write_4byte(dm, 0xeb0, 0x77777777);
		odm_write_4byte(dm, 0xeb4, 0x00007777);
		odm_write_4byte(dm, 0xebc, 0x0000083B);
		ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
			     "[IQK]external PA on!!!!\n");
	} else {
		/*RFE setting*/
		odm_write_4byte(dm, 0xcb0, 0x77777777);
		odm_write_4byte(dm, 0xcb4, 0x00007777);
		odm_write_4byte(dm, 0xcbc, 0x00000100);
		odm_write_4byte(dm, 0xeb0, 0x77777777);
		odm_write_4byte(dm, 0xeb4, 0x00007777);
		odm_write_4byte(dm, 0xebc, 0x00000100);
	}
}