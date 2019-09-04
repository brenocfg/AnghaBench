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
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  process_PWDB (int /*<<< orphan*/ *,union recv_frame*) ; 
 int /*<<< orphan*/  process_link_qual (int /*<<< orphan*/ *,union recv_frame*) ; 
 int /*<<< orphan*/  process_rssi (int /*<<< orphan*/ *,union recv_frame*) ; 

__attribute__((used)) static void process_phy_info(_adapter *padapter, union recv_frame *prframe)
{
	union recv_frame *precvframe = (union recv_frame *)prframe;

#ifdef CONFIG_SW_ANTENNA_DIVERSITY
	// If we switch to the antenna for testing, the signal strength 
	// of the packets in this time shall not be counted into total receiving power. 
	// This prevents error counting Rx signal strength and affecting other dynamic mechanism.

	// Select the packets to do RSSI checking for antenna switching.
	SwAntDivRSSICheck8192C(padapter, precvframe->u.hdr.attrib.RxPWDBAll);

	if(GET_HAL_DATA(padapter)->RSSI_test == _TRUE)
		return;
#endif
	//
	// Check RSSI
	//
	process_rssi(padapter, precvframe);
	//
	// Check PWDB.
	//
	process_PWDB(padapter, precvframe); 
	//
	// Check EVM
	//
	process_link_qual(padapter,  precvframe);

}