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
struct hci_dev {int /*<<< orphan*/ * dev_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dev_class_show(struct seq_file *f, void *ptr)
{
	struct hci_dev *hdev = f->private;

	hci_dev_lock(hdev);
	seq_printf(f, "0x%.2x%.2x%.2x\n", hdev->dev_class[2],
		   hdev->dev_class[1], hdev->dev_class[0]);
	hci_dev_unlock(hdev);

	return 0;
}