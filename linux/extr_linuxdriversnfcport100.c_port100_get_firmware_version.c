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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct port100 {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PORT100_CMD_GET_FIRMWARE_VERSION ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* port100_alloc_skb (struct port100*,int /*<<< orphan*/ ) ; 
 struct sk_buff* port100_send_cmd_sync (struct port100*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static u16 port100_get_firmware_version(struct port100 *dev)
{
	struct sk_buff *skb;
	struct sk_buff *resp;
	u16 fw_ver;

	skb = port100_alloc_skb(dev, 0);
	if (!skb)
		return 0;

	resp = port100_send_cmd_sync(dev, PORT100_CMD_GET_FIRMWARE_VERSION,
				     skb);
	if (IS_ERR(resp))
		return 0;

	fw_ver = le16_to_cpu(*(__le16 *)resp->data);

	dev_kfree_skb(resp);

	return fw_ver;
}