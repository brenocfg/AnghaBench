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
struct discovery_state {int /*<<< orphan*/  last_adv_addr; } ;
struct hci_dev {struct discovery_state discovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_pending_adv_report(struct hci_dev *hdev)
{
	struct discovery_state *d = &hdev->discovery;

	return bacmp(&d->last_adv_addr, BDADDR_ANY);
}