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
struct tcmsg {int dummy; } ;
struct nlmsghdr {int nlmsg_len; } ;
struct nlattr {int dummy; } ;
typedef  int (* libbpf_dump_nlmsg_t ) (void*,struct tcmsg*,struct nlattr**) ;

/* Variables and functions */
 int LIBBPF_ERRNO__NLPARSE ; 
 int NLMSG_ALIGN (int) ; 
 struct tcmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 int NLMSG_LENGTH (int) ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ libbpf_nla_parse (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dump_class_nlmsg(struct nlmsghdr *nlh,
			      libbpf_dump_nlmsg_t dump_class_nlmsg,
			      void *cookie)
{
	struct nlattr *tb[TCA_MAX + 1], *attr;
	struct tcmsg *t = NLMSG_DATA(nlh);
	int len;

	len = nlh->nlmsg_len - NLMSG_LENGTH(sizeof(*t));
	attr = (struct nlattr *) ((void *) t + NLMSG_ALIGN(sizeof(*t)));
	if (libbpf_nla_parse(tb, TCA_MAX, attr, len, NULL) != 0)
		return -LIBBPF_ERRNO__NLPARSE;

	return dump_class_nlmsg(cookie, t, tb);
}