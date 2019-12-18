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

/* Variables and functions */
 int /*<<< orphan*/  WIMAX_GNL_MSG_DATA ; 
 void const* nla_data (struct nlattr*) ; 
 size_t nla_len (struct nlattr*) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

const void *wimax_msg_data_len(struct sk_buff *msg, size_t *size)
{
	struct nlmsghdr *nlh = (void *) msg->head;
	struct nlattr *nla;

	nla = nlmsg_find_attr(nlh, sizeof(struct genlmsghdr),
			      WIMAX_GNL_MSG_DATA);
	if (nla == NULL) {
		pr_err("Cannot find attribute WIMAX_GNL_MSG_DATA\n");
		return NULL;
	}
	*size = nla_len(nla);
	return nla_data(nla);
}