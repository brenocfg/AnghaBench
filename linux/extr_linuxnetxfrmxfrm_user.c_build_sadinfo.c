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
typedef  int /*<<< orphan*/  u32 ;
struct xfrmu_sadhinfo {int /*<<< orphan*/  sadhcnt; int /*<<< orphan*/  sadhmcnt; } ;
struct xfrmk_sadinfo {int /*<<< orphan*/  sadcnt; int /*<<< orphan*/  sadhcnt; int /*<<< orphan*/  sadhmcnt; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  sh ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  XFRMA_SAD_CNT ; 
 int /*<<< orphan*/  XFRMA_SAD_HINFO ; 
 int /*<<< orphan*/  XFRM_MSG_NEWSADINFO ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct xfrmu_sadhinfo*) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/ * nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_sad_getinfo (struct net*,struct xfrmk_sadinfo*) ; 

__attribute__((used)) static int build_sadinfo(struct sk_buff *skb, struct net *net,
			 u32 portid, u32 seq, u32 flags)
{
	struct xfrmk_sadinfo si;
	struct xfrmu_sadhinfo sh;
	struct nlmsghdr *nlh;
	int err;
	u32 *f;

	nlh = nlmsg_put(skb, portid, seq, XFRM_MSG_NEWSADINFO, sizeof(u32), 0);
	if (nlh == NULL) /* shouldn't really happen ... */
		return -EMSGSIZE;

	f = nlmsg_data(nlh);
	*f = flags;
	xfrm_sad_getinfo(net, &si);

	sh.sadhmcnt = si.sadhmcnt;
	sh.sadhcnt = si.sadhcnt;

	err = nla_put_u32(skb, XFRMA_SAD_CNT, si.sadcnt);
	if (!err)
		err = nla_put(skb, XFRMA_SAD_HINFO, sizeof(sh), &sh);
	if (err) {
		nlmsg_cancel(skb, nlh);
		return err;
	}

	nlmsg_end(skb, nlh);
	return 0;
}