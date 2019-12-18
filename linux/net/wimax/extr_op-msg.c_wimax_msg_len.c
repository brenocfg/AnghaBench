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
struct sk_buff {scalar_t__ head; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct genlmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  WIMAX_GNL_MSG_DATA ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

ssize_t wimax_msg_len(struct sk_buff *msg)
{
	struct nlmsghdr *nlh = (void *) msg->head;
	struct nlattr *nla;

	nla = nlmsg_find_attr(nlh, sizeof(struct genlmsghdr),
			      WIMAX_GNL_MSG_DATA);
	if (nla == NULL) {
		pr_err("Cannot find attribute WIMAX_GNL_MSG_DATA\n");
		return -EINVAL;
	}
	return nla_len(nla);
}