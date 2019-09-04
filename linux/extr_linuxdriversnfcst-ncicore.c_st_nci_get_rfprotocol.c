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
struct nci_dev {int dummy; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_PROTO_ISO15693_MASK ; 
 scalar_t__ ST_NCI1_X_PROPRIETARY_ISO15693 ; 

__attribute__((used)) static __u32 st_nci_get_rfprotocol(struct nci_dev *ndev,
					 __u8 rf_protocol)
{
	return rf_protocol == ST_NCI1_X_PROPRIETARY_ISO15693 ?
		NFC_PROTO_ISO15693_MASK : 0;
}