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
struct sk_buff {int len; } ;
struct rtgenmsg {int rtgen_family; } ;
struct netlink_callback {int* args; int /*<<< orphan*/  nlh; } ;
struct neigh_table {int family; } ;
struct ndmsg {scalar_t__ ndm_flags; } ;

/* Variables and functions */
 int NEIGH_NR_TABLES ; 
 scalar_t__ NTF_PROXY ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int neigh_dump_table (struct neigh_table*,struct sk_buff*,struct netlink_callback*) ; 
 struct neigh_table** neigh_tables ; 
 scalar_t__ nlmsg_data (int /*<<< orphan*/ ) ; 
 int nlmsg_len (int /*<<< orphan*/ ) ; 
 int pneigh_dump_table (struct neigh_table*,struct sk_buff*,struct netlink_callback*) ; 

__attribute__((used)) static int neigh_dump_info(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct neigh_table *tbl;
	int t, family, s_t;
	int proxy = 0;
	int err;

	family = ((struct rtgenmsg *) nlmsg_data(cb->nlh))->rtgen_family;

	/* check for full ndmsg structure presence, family member is
	 * the same for both structures
	 */
	if (nlmsg_len(cb->nlh) >= sizeof(struct ndmsg) &&
	    ((struct ndmsg *) nlmsg_data(cb->nlh))->ndm_flags == NTF_PROXY)
		proxy = 1;

	s_t = cb->args[0];

	for (t = 0; t < NEIGH_NR_TABLES; t++) {
		tbl = neigh_tables[t];

		if (!tbl)
			continue;
		if (t < s_t || (family && tbl->family != family))
			continue;
		if (t > s_t)
			memset(&cb->args[1], 0, sizeof(cb->args) -
						sizeof(cb->args[0]));
		if (proxy)
			err = pneigh_dump_table(tbl, skb, cb);
		else
			err = neigh_dump_table(tbl, skb, cb);
		if (err < 0)
			break;
	}

	cb->args[0] = t;
	return skb->len;
}