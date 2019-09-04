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
struct ip_vs_dest {scalar_t__ l_threshold; int flags; int u_threshold; int /*<<< orphan*/  persistconns; int /*<<< orphan*/  activeconns; int /*<<< orphan*/  inactconns; int /*<<< orphan*/  refcnt; } ;
struct ip_vs_conn {int flags; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  state; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  daf; int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  af; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; int /*<<< orphan*/  protocol; struct ip_vs_dest* dest; } ;

/* Variables and functions */
 int IP_VS_CONN_F_INACTIVE ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_DEST_F_OVERLOAD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_dest_put (struct ip_vs_dest*) ; 
 int ip_vs_dest_totalconns (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_fwd_tag (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_proto_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ip_vs_unbind_dest(struct ip_vs_conn *cp)
{
	struct ip_vs_dest *dest = cp->dest;

	if (!dest)
		return;

	IP_VS_DBG_BUF(7, "Unbind-dest %s c:%s:%d v:%s:%d "
		      "d:%s:%d fwd:%c s:%u conn->flags:%X conn->refcnt:%d "
		      "dest->refcnt:%d\n",
		      ip_vs_proto_name(cp->protocol),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->daf, &cp->daddr), ntohs(cp->dport),
		      ip_vs_fwd_tag(cp), cp->state,
		      cp->flags, refcount_read(&cp->refcnt),
		      refcount_read(&dest->refcnt));

	/* Update the connection counters */
	if (!(cp->flags & IP_VS_CONN_F_TEMPLATE)) {
		/* It is a normal connection, so decrease the inactconns
		   or activeconns counter */
		if (cp->flags & IP_VS_CONN_F_INACTIVE) {
			atomic_dec(&dest->inactconns);
		} else {
			atomic_dec(&dest->activeconns);
		}
	} else {
		/* It is a persistent connection/template, so decrease
		   the persistent connection counter */
		atomic_dec(&dest->persistconns);
	}

	if (dest->l_threshold != 0) {
		if (ip_vs_dest_totalconns(dest) < dest->l_threshold)
			dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	} else if (dest->u_threshold != 0) {
		if (ip_vs_dest_totalconns(dest) * 4 < dest->u_threshold * 3)
			dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	} else {
		if (dest->flags & IP_VS_DEST_F_OVERLOAD)
			dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	}

	ip_vs_dest_put(dest);
}