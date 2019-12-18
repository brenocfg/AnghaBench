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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_user_report {int /*<<< orphan*/  sel; int /*<<< orphan*/  proto; } ;
struct xfrm_selector {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  XFRMA_COADDR ; 
 int /*<<< orphan*/  XFRM_MSG_REPORT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct xfrm_selector*,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct xfrm_user_report* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_report(struct sk_buff *skb, u8 proto,
			struct xfrm_selector *sel, xfrm_address_t *addr)
{
	struct xfrm_user_report *ur;
	struct nlmsghdr *nlh;

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_REPORT, sizeof(*ur), 0);
	if (nlh == NULL)
		return -EMSGSIZE;

	ur = nlmsg_data(nlh);
	ur->proto = proto;
	memcpy(&ur->sel, sel, sizeof(ur->sel));

	if (addr) {
		int err = nla_put(skb, XFRMA_COADDR, sizeof(*addr), addr);
		if (err) {
			nlmsg_cancel(skb, nlh);
			return err;
		}
	}
	nlmsg_end(skb, nlh);
	return 0;
}