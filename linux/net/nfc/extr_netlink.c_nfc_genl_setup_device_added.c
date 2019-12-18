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
struct sk_buff {int dummy; } ;
struct nfc_dev {int /*<<< orphan*/  rf_mode; int /*<<< orphan*/  dev_up; int /*<<< orphan*/  supported_protocols; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_ATTR_DEVICE_INDEX ; 
 int /*<<< orphan*/  NFC_ATTR_DEVICE_NAME ; 
 int /*<<< orphan*/  NFC_ATTR_DEVICE_POWERED ; 
 int /*<<< orphan*/  NFC_ATTR_PROTOCOLS ; 
 int /*<<< orphan*/  NFC_ATTR_RF_MODE ; 
 int /*<<< orphan*/  nfc_device_name (struct nfc_dev*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_setup_device_added(struct nfc_dev *dev, struct sk_buff *msg)
{
	if (nla_put_string(msg, NFC_ATTR_DEVICE_NAME, nfc_device_name(dev)) ||
	    nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_PROTOCOLS, dev->supported_protocols) ||
	    nla_put_u8(msg, NFC_ATTR_DEVICE_POWERED, dev->dev_up) ||
	    nla_put_u8(msg, NFC_ATTR_RF_MODE, dev->rf_mode))
		return -1;
	return 0;
}