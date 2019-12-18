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
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int MGMT_PHY_BR_1M_1SLOT ; 
 int MGMT_PHY_LE_1M_RX ; 
 int MGMT_PHY_LE_1M_TX ; 
 int get_supported_phys (struct hci_dev*) ; 

__attribute__((used)) static u32 get_configurable_phys(struct hci_dev *hdev)
{
	return (get_supported_phys(hdev) & ~MGMT_PHY_BR_1M_1SLOT &
		~MGMT_PHY_LE_1M_TX & ~MGMT_PHY_LE_1M_RX);
}