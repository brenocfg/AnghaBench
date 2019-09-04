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
struct l2cap_chan {int dummy; } ;
struct hci_dev {struct l2cap_chan* smp_data; struct l2cap_chan* smp_bredr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_del_chan (struct l2cap_chan*) ; 

void smp_unregister(struct hci_dev *hdev)
{
	struct l2cap_chan *chan;

	if (hdev->smp_bredr_data) {
		chan = hdev->smp_bredr_data;
		hdev->smp_bredr_data = NULL;
		smp_del_chan(chan);
	}

	if (hdev->smp_data) {
		chan = hdev->smp_data;
		hdev->smp_data = NULL;
		smp_del_chan(chan);
	}
}