#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vif_device {TYPE_1__* dev; } ;
struct sk_buff {int dummy; } ;
struct rtnexthop {int rtnh_hops; int rtnh_len; int /*<<< orphan*/  rtnh_ifindex; scalar_t__ rtnh_flags; } ;
struct rtmsg {int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_flags; } ;
struct rta_mfc_stats {int /*<<< orphan*/  mfcs_wrong_if; int /*<<< orphan*/  mfcs_bytes; int /*<<< orphan*/  mfcs_packets; } ;
struct nlattr {int dummy; } ;
struct mr_table {struct vif_device* vif_table; } ;
struct TYPE_5__ {int minvif; int maxvif; int* ttls; int /*<<< orphan*/  wrong_if; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkt; int /*<<< orphan*/  lastuse; } ;
struct TYPE_6__ {TYPE_2__ res; } ;
struct mr_mfc {int mfc_parent; int mfc_flags; TYPE_3__ mfc_un; } ;
typedef  int /*<<< orphan*/  mfcs ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOENT ; 
 int MAXVIFS ; 
 int MFC_OFFLOAD ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTA_EXPIRES ; 
 int /*<<< orphan*/  RTA_IIF ; 
 int /*<<< orphan*/  RTA_MFC_STATS ; 
 int /*<<< orphan*/  RTA_MULTIPATH ; 
 int /*<<< orphan*/  RTA_PAD ; 
 int /*<<< orphan*/  RTNH_F_OFFLOAD ; 
 int /*<<< orphan*/  RTNH_F_UNRESOLVED ; 
 int /*<<< orphan*/  RTN_MULTICAST ; 
 scalar_t__ VIF_EXISTS (struct mr_table*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_clock_t (unsigned long) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct rta_mfc_stats*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtnexthop* nla_reserve_nohdr (struct sk_buff*,int) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int mr_fill_mroute(struct mr_table *mrt, struct sk_buff *skb,
		   struct mr_mfc *c, struct rtmsg *rtm)
{
	struct rta_mfc_stats mfcs;
	struct nlattr *mp_attr;
	struct rtnexthop *nhp;
	unsigned long lastuse;
	int ct;

	/* If cache is unresolved, don't try to parse IIF and OIF */
	if (c->mfc_parent >= MAXVIFS) {
		rtm->rtm_flags |= RTNH_F_UNRESOLVED;
		return -ENOENT;
	}

	if (VIF_EXISTS(mrt, c->mfc_parent) &&
	    nla_put_u32(skb, RTA_IIF,
			mrt->vif_table[c->mfc_parent].dev->ifindex) < 0)
		return -EMSGSIZE;

	if (c->mfc_flags & MFC_OFFLOAD)
		rtm->rtm_flags |= RTNH_F_OFFLOAD;

	mp_attr = nla_nest_start_noflag(skb, RTA_MULTIPATH);
	if (!mp_attr)
		return -EMSGSIZE;

	for (ct = c->mfc_un.res.minvif; ct < c->mfc_un.res.maxvif; ct++) {
		if (VIF_EXISTS(mrt, ct) && c->mfc_un.res.ttls[ct] < 255) {
			struct vif_device *vif;

			nhp = nla_reserve_nohdr(skb, sizeof(*nhp));
			if (!nhp) {
				nla_nest_cancel(skb, mp_attr);
				return -EMSGSIZE;
			}

			nhp->rtnh_flags = 0;
			nhp->rtnh_hops = c->mfc_un.res.ttls[ct];
			vif = &mrt->vif_table[ct];
			nhp->rtnh_ifindex = vif->dev->ifindex;
			nhp->rtnh_len = sizeof(*nhp);
		}
	}

	nla_nest_end(skb, mp_attr);

	lastuse = READ_ONCE(c->mfc_un.res.lastuse);
	lastuse = time_after_eq(jiffies, lastuse) ? jiffies - lastuse : 0;

	mfcs.mfcs_packets = c->mfc_un.res.pkt;
	mfcs.mfcs_bytes = c->mfc_un.res.bytes;
	mfcs.mfcs_wrong_if = c->mfc_un.res.wrong_if;
	if (nla_put_64bit(skb, RTA_MFC_STATS, sizeof(mfcs), &mfcs, RTA_PAD) ||
	    nla_put_u64_64bit(skb, RTA_EXPIRES, jiffies_to_clock_t(lastuse),
			      RTA_PAD))
		return -EMSGSIZE;

	rtm->rtm_type = RTN_MULTICAST;
	return 1;
}