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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
typedef  int /*<<< orphan*/  u16 ;
struct ip_vs_lblc_table {int dummy; } ;
struct ip_vs_lblc_entry {struct ip_vs_dest* dest; int /*<<< orphan*/  lastuse; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;
struct ip_vs_dest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ip_vs_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union nf_inet_addr const*) ; 
 int /*<<< orphan*/  ip_vs_dest_hold (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_lblc_del (struct ip_vs_lblc_entry*) ; 
 struct ip_vs_lblc_entry* ip_vs_lblc_get (int /*<<< orphan*/ ,struct ip_vs_lblc_table*,union nf_inet_addr const*) ; 
 int /*<<< orphan*/  ip_vs_lblc_hash (struct ip_vs_lblc_table*,struct ip_vs_lblc_entry*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ip_vs_lblc_entry* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ip_vs_lblc_entry *
ip_vs_lblc_new(struct ip_vs_lblc_table *tbl, const union nf_inet_addr *daddr,
	       u16 af, struct ip_vs_dest *dest)
{
	struct ip_vs_lblc_entry *en;

	en = ip_vs_lblc_get(af, tbl, daddr);
	if (en) {
		if (en->dest == dest)
			return en;
		ip_vs_lblc_del(en);
	}
	en = kmalloc(sizeof(*en), GFP_ATOMIC);
	if (!en)
		return NULL;

	en->af = af;
	ip_vs_addr_copy(af, &en->addr, daddr);
	en->lastuse = jiffies;

	ip_vs_dest_hold(dest);
	en->dest = dest;

	ip_vs_lblc_hash(tbl, en);

	return en;
}