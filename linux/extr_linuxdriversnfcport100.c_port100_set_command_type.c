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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int* data; } ;
struct port100 {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PORT100_CMD_SET_COMMAND_TYPE ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* port100_alloc_skb (struct port100*,int) ; 
 struct sk_buff* port100_send_cmd_sync (struct port100*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port100_set_command_type(struct port100 *dev, u8 command_type)
{
	struct sk_buff *skb;
	struct sk_buff *resp;
	int rc;

	skb = port100_alloc_skb(dev, 1);
	if (!skb)
		return -ENOMEM;

	skb_put_u8(skb, command_type);

	resp = port100_send_cmd_sync(dev, PORT100_CMD_SET_COMMAND_TYPE, skb);
	if (IS_ERR(resp))
		return PTR_ERR(resp);

	rc = resp->data[0];

	dev_kfree_skb(resp);

	return rc;
}