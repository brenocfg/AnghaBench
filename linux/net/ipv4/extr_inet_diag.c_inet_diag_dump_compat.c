#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; } ;
struct inet_diag_req_v2 {int /*<<< orphan*/  id; int /*<<< orphan*/  idiag_states; int /*<<< orphan*/  idiag_ext; int /*<<< orphan*/  sdiag_protocol; int /*<<< orphan*/  sdiag_family; } ;
struct inet_diag_req {int /*<<< orphan*/  id; int /*<<< orphan*/  idiag_states; int /*<<< orphan*/  idiag_ext; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  INET_DIAG_REQ_BYTECODE ; 
 int __inet_diag_dump (struct sk_buff*,struct netlink_callback*,struct inet_diag_req_v2*,struct nlattr*) ; 
 int /*<<< orphan*/  inet_diag_type2proto (int /*<<< orphan*/ ) ; 
 scalar_t__ nlmsg_attrlen (TYPE_1__*,int) ; 
 struct inet_diag_req* nlmsg_data (TYPE_1__*) ; 
 struct nlattr* nlmsg_find_attr (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_diag_dump_compat(struct sk_buff *skb,
				 struct netlink_callback *cb)
{
	struct inet_diag_req *rc = nlmsg_data(cb->nlh);
	int hdrlen = sizeof(struct inet_diag_req);
	struct inet_diag_req_v2 req;
	struct nlattr *bc = NULL;

	req.sdiag_family = AF_UNSPEC; /* compatibility */
	req.sdiag_protocol = inet_diag_type2proto(cb->nlh->nlmsg_type);
	req.idiag_ext = rc->idiag_ext;
	req.idiag_states = rc->idiag_states;
	req.id = rc->id;

	if (nlmsg_attrlen(cb->nlh, hdrlen))
		bc = nlmsg_find_attr(cb->nlh, hdrlen, INET_DIAG_REQ_BYTECODE);

	return __inet_diag_dump(skb, cb, &req, bc);
}