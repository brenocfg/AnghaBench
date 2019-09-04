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
struct ip_vs_dest {scalar_t__ u_threshold; int /*<<< orphan*/  flags; int /*<<< orphan*/  persistconns; int /*<<< orphan*/  inactconns; int /*<<< orphan*/  activeconns; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  conn_flags; } ;
struct ip_vs_conn {scalar_t__ protocol; int flags; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  state; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  daf; int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  af; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; struct ip_vs_dest* dest; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int IP_VS_CONN_F_FWD_MASK ; 
 unsigned int IP_VS_CONN_F_INACTIVE ; 
 int IP_VS_CONN_F_NOOUTPUT ; 
 unsigned int IP_VS_CONN_F_ONE_PACKET ; 
 int IP_VS_CONN_F_SYNC ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_VS_DEST_F_OVERLOAD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_dest_hold (struct ip_vs_dest*) ; 
 scalar_t__ ip_vs_dest_totalconns (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_fwd_tag (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_proto_name (scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ip_vs_bind_dest(struct ip_vs_conn *cp, struct ip_vs_dest *dest)
{
	unsigned int conn_flags;
	__u32 flags;

	/* if dest is NULL, then return directly */
	if (!dest)
		return;

	/* Increase the refcnt counter of the dest */
	ip_vs_dest_hold(dest);

	conn_flags = atomic_read(&dest->conn_flags);
	if (cp->protocol != IPPROTO_UDP)
		conn_flags &= ~IP_VS_CONN_F_ONE_PACKET;
	flags = cp->flags;
	/* Bind with the destination and its corresponding transmitter */
	if (flags & IP_VS_CONN_F_SYNC) {
		/* if the connection is not template and is created
		 * by sync, preserve the activity flag.
		 */
		if (!(flags & IP_VS_CONN_F_TEMPLATE))
			conn_flags &= ~IP_VS_CONN_F_INACTIVE;
		/* connections inherit forwarding method from dest */
		flags &= ~(IP_VS_CONN_F_FWD_MASK | IP_VS_CONN_F_NOOUTPUT);
	}
	flags |= conn_flags;
	cp->flags = flags;
	cp->dest = dest;

	IP_VS_DBG_BUF(7, "Bind-dest %s c:%s:%d v:%s:%d "
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
	if (!(flags & IP_VS_CONN_F_TEMPLATE)) {
		/* It is a normal connection, so modify the counters
		 * according to the flags, later the protocol can
		 * update them on state change
		 */
		if (!(flags & IP_VS_CONN_F_INACTIVE))
			atomic_inc(&dest->activeconns);
		else
			atomic_inc(&dest->inactconns);
	} else {
		/* It is a persistent connection/template, so increase
		   the persistent connection counter */
		atomic_inc(&dest->persistconns);
	}

	if (dest->u_threshold != 0 &&
	    ip_vs_dest_totalconns(dest) >= dest->u_threshold)
		dest->flags |= IP_VS_DEST_F_OVERLOAD;
}