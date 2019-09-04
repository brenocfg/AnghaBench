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
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_LA_SEL_INFO ; 
 int NCI_LA_SEL_INFO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  NCI_LF_CON_BITR_F ; 
 int NCI_LF_CON_BITR_F_212 ; 
 int NCI_LF_CON_BITR_F_424 ; 
 int /*<<< orphan*/  NCI_LF_PROTOCOL_TYPE ; 
 int NCI_LF_PROTOCOL_TYPE_NFC_DEP_MASK ; 
 int nci_set_config (struct nci_dev*,int /*<<< orphan*/ ,int,int*) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 

__attribute__((used)) static int nci_set_listen_parameters(struct nfc_dev *nfc_dev)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	int rc;
	__u8 val;

	val = NCI_LA_SEL_INFO_NFC_DEP_MASK;

	rc = nci_set_config(ndev, NCI_LA_SEL_INFO, 1, &val);
	if (rc)
		return rc;

	val = NCI_LF_PROTOCOL_TYPE_NFC_DEP_MASK;

	rc = nci_set_config(ndev, NCI_LF_PROTOCOL_TYPE, 1, &val);
	if (rc)
		return rc;

	val = NCI_LF_CON_BITR_F_212 | NCI_LF_CON_BITR_F_424;

	return nci_set_config(ndev, NCI_LF_CON_BITR_F, 1, &val);
}