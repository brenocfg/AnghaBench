#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct nci_dev {TYPE_1__* hci_dev; } ;
struct TYPE_4__ {scalar_t__ host; int /*<<< orphan*/  gate; } ;
struct TYPE_3__ {TYPE_2__* pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_HCI_INVALID_GATE ; 
 scalar_t__ NCI_HCI_INVALID_HOST ; 
 int NCI_HCI_MAX_PIPES ; 

__attribute__((used)) static void nci_hci_reset_pipes_per_host(struct nci_dev *ndev, u8 host)
{
	int i;

	for (i = 0; i < NCI_HCI_MAX_PIPES; i++) {
		if (ndev->hci_dev->pipes[i].host == host) {
			ndev->hci_dev->pipes[i].gate = NCI_HCI_INVALID_GATE;
			ndev->hci_dev->pipes[i].host = NCI_HCI_INVALID_HOST;
		}
	}
}