#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  family; } ;
struct TYPE_5__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_state {int replay_maxdiff; int replay_maxage; int /*<<< orphan*/  if_id; int /*<<< orphan*/  mark; int /*<<< orphan*/  curlft; int /*<<< orphan*/  replay; int /*<<< orphan*/ * replay_esn; TYPE_2__ props; TYPE_1__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  family; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_aevent_id {int flags; int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; TYPE_4__ sa_id; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct TYPE_7__ {int aevent; } ;
struct km_event {TYPE_3__ data; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int HZ ; 
 int /*<<< orphan*/  XFRMA_ETIMER_THRESH ; 
 int /*<<< orphan*/  XFRMA_LTIME_VAL ; 
 int /*<<< orphan*/  XFRMA_PAD ; 
 int /*<<< orphan*/  XFRMA_REPLAY_ESN_VAL ; 
 int /*<<< orphan*/  XFRMA_REPLAY_THRESH ; 
 int /*<<< orphan*/  XFRMA_REPLAY_VAL ; 
 int XFRM_AE_ETHR ; 
 int XFRM_AE_RTHR ; 
 int /*<<< orphan*/  XFRM_MSG_NEWAE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct xfrm_aevent_id* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int xfrm_if_id_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int xfrm_mark_put (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int xfrm_replay_state_esn_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_aevent(struct sk_buff *skb, struct xfrm_state *x, const struct km_event *c)
{
	struct xfrm_aevent_id *id;
	struct nlmsghdr *nlh;
	int err;

	nlh = nlmsg_put(skb, c->portid, c->seq, XFRM_MSG_NEWAE, sizeof(*id), 0);
	if (nlh == NULL)
		return -EMSGSIZE;

	id = nlmsg_data(nlh);
	memset(&id->sa_id, 0, sizeof(id->sa_id));
	memcpy(&id->sa_id.daddr, &x->id.daddr, sizeof(x->id.daddr));
	id->sa_id.spi = x->id.spi;
	id->sa_id.family = x->props.family;
	id->sa_id.proto = x->id.proto;
	memcpy(&id->saddr, &x->props.saddr, sizeof(x->props.saddr));
	id->reqid = x->props.reqid;
	id->flags = c->data.aevent;

	if (x->replay_esn) {
		err = nla_put(skb, XFRMA_REPLAY_ESN_VAL,
			      xfrm_replay_state_esn_len(x->replay_esn),
			      x->replay_esn);
	} else {
		err = nla_put(skb, XFRMA_REPLAY_VAL, sizeof(x->replay),
			      &x->replay);
	}
	if (err)
		goto out_cancel;
	err = nla_put_64bit(skb, XFRMA_LTIME_VAL, sizeof(x->curlft), &x->curlft,
			    XFRMA_PAD);
	if (err)
		goto out_cancel;

	if (id->flags & XFRM_AE_RTHR) {
		err = nla_put_u32(skb, XFRMA_REPLAY_THRESH, x->replay_maxdiff);
		if (err)
			goto out_cancel;
	}
	if (id->flags & XFRM_AE_ETHR) {
		err = nla_put_u32(skb, XFRMA_ETIMER_THRESH,
				  x->replay_maxage * 10 / HZ);
		if (err)
			goto out_cancel;
	}
	err = xfrm_mark_put(skb, &x->mark);
	if (err)
		goto out_cancel;

	err = xfrm_if_id_put(skb, x->if_id);
	if (err)
		goto out_cancel;

	nlmsg_end(skb, nlh);
	return 0;

out_cancel:
	nlmsg_cancel(skb, nlh);
	return err;
}