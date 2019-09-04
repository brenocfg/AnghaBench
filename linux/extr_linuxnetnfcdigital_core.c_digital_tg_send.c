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
struct nfc_digital_dev {int dummy; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int digital_tg_send_dep_res (struct nfc_digital_dev*,struct sk_buff*) ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 

__attribute__((used)) static int digital_tg_send(struct nfc_dev *dev, struct sk_buff *skb)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(dev);

	return digital_tg_send_dep_res(ddev, skb);
}