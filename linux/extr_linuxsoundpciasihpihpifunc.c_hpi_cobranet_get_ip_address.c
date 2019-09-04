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
 int /*<<< orphan*/  HPI_COBRANET_HMI_cobra_ip_mon_currentIP ; 
 scalar_t__ hpi_cobranet_hmi_read (int,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 

u16 hpi_cobranet_get_ip_address(u32 h_control, u32 *pdw_ip_address)
{
	u32 byte_count;
	u32 iP;
	u16 err;

	err = hpi_cobranet_hmi_read(h_control,
		HPI_COBRANET_HMI_cobra_ip_mon_currentIP, 4, &byte_count,
		(u8 *)&iP);

	*pdw_ip_address =
		((iP & 0xff000000) >> 8) | ((iP & 0x00ff0000) << 8) | ((iP &
			0x0000ff00) >> 8) | ((iP & 0x000000ff) << 8);

	if (err)
		*pdw_ip_address = 0;

	return err;

}