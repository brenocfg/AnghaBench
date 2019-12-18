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
typedef  int u8 ;
struct smp_ltk {int dummy; } ;
struct smp_cmd_master_ident {int /*<<< orphan*/  rand; int /*<<< orphan*/  ediv; } ;
struct smp_chan {int remote_key_dist; struct smp_ltk* ltk; int /*<<< orphan*/  enc_key_size; int /*<<< orphan*/  tk; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_conn {struct hci_conn* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {scalar_t__ sec_level; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 int KEY_DIST_MASK ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_IDENT_INFO ; 
 int /*<<< orphan*/  SMP_CMD_SIGN_INFO ; 
 int SMP_DIST_ENC_KEY ; 
 int SMP_DIST_ID_KEY ; 
 int SMP_DIST_SIGN ; 
 int SMP_INVALID_PARAMS ; 
 int /*<<< orphan*/  SMP_LTK ; 
 struct smp_ltk* hci_add_ltk (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  smp_distribute_keys (struct smp_chan*) ; 

__attribute__((used)) static int smp_cmd_master_ident(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct smp_cmd_master_ident *rp = (void *) skb->data;
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;
	struct hci_dev *hdev = conn->hcon->hdev;
	struct hci_conn *hcon = conn->hcon;
	struct smp_ltk *ltk;
	u8 authenticated;

	BT_DBG("conn %p", conn);

	if (skb->len < sizeof(*rp))
		return SMP_INVALID_PARAMS;

	/* Mark the information as received */
	smp->remote_key_dist &= ~SMP_DIST_ENC_KEY;

	if (smp->remote_key_dist & SMP_DIST_ID_KEY)
		SMP_ALLOW_CMD(smp, SMP_CMD_IDENT_INFO);
	else if (smp->remote_key_dist & SMP_DIST_SIGN)
		SMP_ALLOW_CMD(smp, SMP_CMD_SIGN_INFO);

	skb_pull(skb, sizeof(*rp));

	authenticated = (hcon->sec_level == BT_SECURITY_HIGH);
	ltk = hci_add_ltk(hdev, &hcon->dst, hcon->dst_type, SMP_LTK,
			  authenticated, smp->tk, smp->enc_key_size,
			  rp->ediv, rp->rand);
	smp->ltk = ltk;
	if (!(smp->remote_key_dist & KEY_DIST_MASK))
		smp_distribute_keys(smp);

	return 0;
}