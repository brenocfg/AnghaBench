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
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfc_hci_failure (struct nfc_hci_dev*,int) ; 

__attribute__((used)) static void nfc_hci_llc_failure(struct nfc_hci_dev *hdev, int err)
{
	nfc_hci_failure(hdev, err);
}