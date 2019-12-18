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
typedef  int u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ HPI_COBRANET_HMI_cobra_if_phy_address ; 
 scalar_t__ hpi_cobranet_hmi_read (int,scalar_t__,int,int*,int /*<<< orphan*/ *) ; 

u16 hpi_cobranet_get_macaddress(u32 h_control, u32 *p_mac_msbs,
	u32 *p_mac_lsbs)
{
	u32 byte_count;
	u16 err;
	u32 mac;

	err = hpi_cobranet_hmi_read(h_control,
		HPI_COBRANET_HMI_cobra_if_phy_address, 4, &byte_count,
		(u8 *)&mac);

	if (!err) {
		*p_mac_msbs =
			((mac & 0xff000000) >> 8) | ((mac & 0x00ff0000) << 8)
			| ((mac & 0x0000ff00) >> 8) | ((mac & 0x000000ff) <<
			8);

		err = hpi_cobranet_hmi_read(h_control,
			HPI_COBRANET_HMI_cobra_if_phy_address + 1, 4,
			&byte_count, (u8 *)&mac);
	}

	if (!err) {
		*p_mac_lsbs =
			((mac & 0xff000000) >> 8) | ((mac & 0x00ff0000) << 8)
			| ((mac & 0x0000ff00) >> 8) | ((mac & 0x000000ff) <<
			8);
	} else {
		*p_mac_msbs = 0;
		*p_mac_lsbs = 0;
	}

	return err;
}