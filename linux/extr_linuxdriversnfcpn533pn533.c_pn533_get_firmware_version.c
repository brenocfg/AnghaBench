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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct pn533_fw_version {int /*<<< orphan*/  support; int /*<<< orphan*/  rev; int /*<<< orphan*/  ver; int /*<<< orphan*/  ic; } ;
struct pn533 {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PN533_CMD_GET_FIRMWARE_VERSION ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* pn533_alloc_skb (struct pn533*,int /*<<< orphan*/ ) ; 
 struct sk_buff* pn533_send_cmd_sync (struct pn533*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int pn533_get_firmware_version(struct pn533 *dev,
				      struct pn533_fw_version *fv)
{
	struct sk_buff *skb;
	struct sk_buff *resp;

	skb = pn533_alloc_skb(dev, 0);
	if (!skb)
		return -ENOMEM;

	resp = pn533_send_cmd_sync(dev, PN533_CMD_GET_FIRMWARE_VERSION, skb);
	if (IS_ERR(resp))
		return PTR_ERR(resp);

	fv->ic = resp->data[0];
	fv->ver = resp->data[1];
	fv->rev = resp->data[2];
	fv->support = resp->data[3];

	dev_kfree_skb(resp);
	return 0;
}