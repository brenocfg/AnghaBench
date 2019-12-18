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
struct nlmsghdr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct nfnl_err {int err; int /*<<< orphan*/  head; struct netlink_ext_ack extack; struct nlmsghdr* nlh; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfnl_err* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int nfnl_err_add(struct list_head *list, struct nlmsghdr *nlh, int err,
			const struct netlink_ext_ack *extack)
{
	struct nfnl_err *nfnl_err;

	nfnl_err = kmalloc(sizeof(struct nfnl_err), GFP_KERNEL);
	if (nfnl_err == NULL)
		return -ENOMEM;

	nfnl_err->nlh = nlh;
	nfnl_err->err = err;
	nfnl_err->extack = *extack;
	list_add_tail(&nfnl_err->head, list);

	return 0;
}