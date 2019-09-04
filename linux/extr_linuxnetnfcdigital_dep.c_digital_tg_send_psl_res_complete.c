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
typedef  unsigned long u8 ;
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_RF_TECH ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_tg_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  digital_tg_listen (struct nfc_digital_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digital_tg_recv_dep_req ; 
 int /*<<< orphan*/  digital_tg_set_rf_tech (struct nfc_digital_dev*,unsigned long) ; 

__attribute__((used)) static void digital_tg_send_psl_res_complete(struct nfc_digital_dev *ddev,
					     void *arg, struct sk_buff *resp)
{
	u8 rf_tech = (unsigned long)arg;

	if (IS_ERR(resp))
		return;

	digital_tg_set_rf_tech(ddev, rf_tech);

	digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH, rf_tech);

	digital_tg_listen(ddev, 1500, digital_tg_recv_dep_req, NULL);

	dev_kfree_skb(resp);
}