#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct smp_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/  prnd; int /*<<< orphan*/  pcnf; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct l2cap_conn {TYPE_1__* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct TYPE_2__ {scalar_t__ out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*,char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RANDOM ; 
 int /*<<< orphan*/  SMP_FLAG_CFM_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_REMOTE_PK ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int /*<<< orphan*/  SMP_FLAG_TK_VALID ; 
 int SMP_INVALID_PARAMS ; 
 int fixup_sc_false_positive (struct smp_chan*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sc_check_confirm (struct smp_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int smp_confirm (struct smp_chan*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 smp_cmd_pairing_confirm(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;

	BT_DBG("conn %p %s", conn, conn->hcon->out ? "master" : "slave");

	if (skb->len < sizeof(smp->pcnf))
		return SMP_INVALID_PARAMS;

	memcpy(smp->pcnf, skb->data, sizeof(smp->pcnf));
	skb_pull(skb, sizeof(smp->pcnf));

	if (test_bit(SMP_FLAG_SC, &smp->flags)) {
		int ret;

		/* Public Key exchange must happen before any other steps */
		if (test_bit(SMP_FLAG_REMOTE_PK, &smp->flags))
			return sc_check_confirm(smp);

		BT_ERR("Unexpected SMP Pairing Confirm");

		ret = fixup_sc_false_positive(smp);
		if (ret)
			return ret;
	}

	if (conn->hcon->out) {
		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, sizeof(smp->prnd),
			     smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);
		return 0;
	}

	if (test_bit(SMP_FLAG_TK_VALID, &smp->flags))
		return smp_confirm(smp);

	set_bit(SMP_FLAG_CFM_PENDING, &smp->flags);

	return 0;
}