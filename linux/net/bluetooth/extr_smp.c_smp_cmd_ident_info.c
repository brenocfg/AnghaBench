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
struct smp_cmd_ident_info {int /*<<< orphan*/  irk; } ;
struct smp_chan {int /*<<< orphan*/  irk; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_conn {struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_IDENT_ADDR_INFO ; 
 int SMP_INVALID_PARAMS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int smp_cmd_ident_info(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct smp_cmd_ident_info *info = (void *) skb->data;
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;

	BT_DBG("");

	if (skb->len < sizeof(*info))
		return SMP_INVALID_PARAMS;

	SMP_ALLOW_CMD(smp, SMP_CMD_IDENT_ADDR_INFO);

	skb_pull(skb, sizeof(*info));

	memcpy(smp->irk, info->irk, 16);

	return 0;
}