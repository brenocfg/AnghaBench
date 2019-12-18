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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_type; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  DCCPDIAG_GETSOCK 131 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  SOCK_DESTROY 130 
#define  SOCK_DIAG_BY_FAMILY 129 
#define  TCPDIAG_GETSOCK 128 
 int __sock_diag_cmd (struct sk_buff*,struct nlmsghdr*) ; 
 int inet_rcv_compat (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_diag_table_mutex ; 
 int /*<<< orphan*/  sock_load_diag_module (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sock_diag_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	int ret;

	switch (nlh->nlmsg_type) {
	case TCPDIAG_GETSOCK:
	case DCCPDIAG_GETSOCK:
		if (inet_rcv_compat == NULL)
			sock_load_diag_module(AF_INET, 0);

		mutex_lock(&sock_diag_table_mutex);
		if (inet_rcv_compat != NULL)
			ret = inet_rcv_compat(skb, nlh);
		else
			ret = -EOPNOTSUPP;
		mutex_unlock(&sock_diag_table_mutex);

		return ret;
	case SOCK_DIAG_BY_FAMILY:
	case SOCK_DESTROY:
		return __sock_diag_cmd(skb, nlh);
	default:
		return -EINVAL;
	}
}