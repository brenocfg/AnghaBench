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
struct rf_tech_specific_params_nfcv_poll {int /*<<< orphan*/  uid; int /*<<< orphan*/  dsfid; } ;
struct nci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_ISO15693_UID_MAXSIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u8 *nci_extract_rf_params_nfcv_passive_poll(struct nci_dev *ndev,
			struct rf_tech_specific_params_nfcv_poll *nfcv_poll,
						     __u8 *data)
{
	++data;
	nfcv_poll->dsfid = *data++;
	memcpy(nfcv_poll->uid, data, NFC_ISO15693_UID_MAXSIZE);
	data += NFC_ISO15693_UID_MAXSIZE;
	return data;
}