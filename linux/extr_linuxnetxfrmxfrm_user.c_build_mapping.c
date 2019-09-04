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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct TYPE_5__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  family; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_user_mapping {int /*<<< orphan*/  reqid; int /*<<< orphan*/  old_sport; int /*<<< orphan*/  new_sport; int /*<<< orphan*/  old_saddr; int /*<<< orphan*/  new_saddr; TYPE_1__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  family; } ;
struct TYPE_6__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_state {TYPE_4__ props; TYPE_3__* encap; TYPE_2__ id; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_7__ {int /*<<< orphan*/  encap_sport; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  XFRM_MSG_MAPPING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct xfrm_user_mapping* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_mapping(struct sk_buff *skb, struct xfrm_state *x,
			 xfrm_address_t *new_saddr, __be16 new_sport)
{
	struct xfrm_user_mapping *um;
	struct nlmsghdr *nlh;

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_MAPPING, sizeof(*um), 0);
	if (nlh == NULL)
		return -EMSGSIZE;

	um = nlmsg_data(nlh);

	memcpy(&um->id.daddr, &x->id.daddr, sizeof(um->id.daddr));
	um->id.spi = x->id.spi;
	um->id.family = x->props.family;
	um->id.proto = x->id.proto;
	memcpy(&um->new_saddr, new_saddr, sizeof(um->new_saddr));
	memcpy(&um->old_saddr, &x->props.saddr, sizeof(um->old_saddr));
	um->new_sport = new_sport;
	um->old_sport = x->encap->encap_sport;
	um->reqid = x->props.reqid;

	nlmsg_end(skb, nlh);
	return 0;
}