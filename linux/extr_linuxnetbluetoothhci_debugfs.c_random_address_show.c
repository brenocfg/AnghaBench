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
struct seq_file {struct hci_dev* private; } ;
struct hci_dev {int /*<<< orphan*/  random_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int random_address_show(struct seq_file *f, void *p)
{
	struct hci_dev *hdev = f->private;

	hci_dev_lock(hdev);
	seq_printf(f, "%pMR\n", &hdev->random_addr);
	hci_dev_unlock(hdev);

	return 0;
}