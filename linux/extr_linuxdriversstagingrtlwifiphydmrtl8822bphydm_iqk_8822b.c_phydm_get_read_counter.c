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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ODM_delay_ms (int) ; 
 int odm_read_4byte (struct phy_dm_struct*,int) ; 

__attribute__((used)) static inline void phydm_get_read_counter(struct phy_dm_struct *dm)
{
	u32 counter = 0x0;

	while (1) {
		if (((odm_read_4byte(dm, 0x1bf0) >> 24) == 0x7f) ||
		    (counter > 300))
			break;

		counter++;
		ODM_delay_ms(1);
	}

	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION, "[IQK]counter = %d\n", counter);
}