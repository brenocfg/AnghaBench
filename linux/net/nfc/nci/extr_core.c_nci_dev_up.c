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
struct nfc_dev {int dummy; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int nci_open_device (struct nci_dev*) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 

__attribute__((used)) static int nci_dev_up(struct nfc_dev *nfc_dev)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	return nci_open_device(ndev);
}