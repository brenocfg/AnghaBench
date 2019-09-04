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
typedef  size_t u8 ;
struct seq_file {struct hci_dev* private; } ;
struct hci_dev {size_t max_page; int /*<<< orphan*/  le_features; int /*<<< orphan*/ * features; } ;

/* Variables and functions */
 size_t HCI_MAX_PAGES ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,size_t,...) ; 

__attribute__((used)) static int features_show(struct seq_file *f, void *ptr)
{
	struct hci_dev *hdev = f->private;
	u8 p;

	hci_dev_lock(hdev);
	for (p = 0; p < HCI_MAX_PAGES && p <= hdev->max_page; p++)
		seq_printf(f, "%2u: %8ph\n", p, hdev->features[p]);
	if (lmp_le_capable(hdev))
		seq_printf(f, "LE: %8ph\n", hdev->le_features);
	hci_dev_unlock(hdev);

	return 0;
}