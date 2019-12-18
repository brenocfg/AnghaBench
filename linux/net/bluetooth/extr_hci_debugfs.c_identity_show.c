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
struct seq_file {struct hci_dev* private; } ;
struct hci_dev {int /*<<< orphan*/  rpa; int /*<<< orphan*/  irk; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  hci_copy_identity_address (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int identity_show(struct seq_file *f, void *p)
{
	struct hci_dev *hdev = f->private;
	bdaddr_t addr;
	u8 addr_type;

	hci_dev_lock(hdev);

	hci_copy_identity_address(hdev, &addr, &addr_type);

	seq_printf(f, "%pMR (type %u) %*phN %pMR\n", &addr, addr_type,
		   16, hdev->irk, &hdev->rpa);

	hci_dev_unlock(hdev);

	return 0;
}