#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfc_hci_dev {int dummy; } ;
struct microread_info {int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
struct TYPE_2__ {int (* enable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct microread_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int microread_open(struct nfc_hci_dev *hdev)
{
	struct microread_info *info = nfc_hci_get_clientdata(hdev);

	return info->phy_ops->enable(info->phy_id);
}