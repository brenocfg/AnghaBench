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
struct nci_dev {int /*<<< orphan*/  nfc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nci_dev*) ; 
 int /*<<< orphan*/  nfc_free_device (int /*<<< orphan*/ ) ; 

void nci_free_device(struct nci_dev *ndev)
{
	nfc_free_device(ndev->nfc_dev);
	kfree(ndev);
}