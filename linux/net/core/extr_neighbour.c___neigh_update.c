#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct neighbour {int nud_state; int* ha; int /*<<< orphan*/  lock; scalar_t__ arp_queue_len_bytes; int /*<<< orphan*/  arp_queue; int /*<<< orphan*/  (* output ) (struct neighbour*,struct sk_buff*) ;TYPE_1__* parms; void* confirmed; int /*<<< orphan*/  ha_lock; int /*<<< orphan*/  probes; void* updated; scalar_t__ dead; struct net_device* dev; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reachable_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_REACHABLE_TIME ; 
 int EINVAL ; 
 int EPERM ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NEIGH_UPDATE_F_OVERRIDE_ISROUTER ; 
 int NEIGH_UPDATE_F_WEAK_OVERRIDE ; 
 int NEIGH_VAR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int NUD_CONNECTED ; 
 int NUD_FAILED ; 
 int NUD_INCOMPLETE ; 
 int NUD_IN_TIMER ; 
 int NUD_NOARP ; 
 int NUD_PERMANENT ; 
 int NUD_PROBE ; 
 int NUD_REACHABLE ; 
 int NUD_STALE ; 
 int NUD_VALID ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct neighbour* dst_neigh_lookup_skb (struct dst_entry*,struct sk_buff*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  memcmp (int const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int const**,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_add_timer (struct neighbour*,void*) ; 
 int /*<<< orphan*/  neigh_connect (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_del_timer (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_invalidate (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_suspect (struct neighbour*) ; 
 int neigh_update_ext_learned (struct neighbour*,int,int*) ; 
 int /*<<< orphan*/  neigh_update_gc_list (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_update_hhs (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_update_is_router (struct neighbour*,int,int*) ; 
 int /*<<< orphan*/  neigh_update_notify (struct neighbour*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct neighbour*,struct sk_buff*) ; 
 int /*<<< orphan*/  trace_neigh_update (struct neighbour*,int const*,int,int,int) ; 
 int /*<<< orphan*/  trace_neigh_update_done (struct neighbour*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __neigh_update(struct neighbour *neigh, const u8 *lladdr,
			  u8 new, u32 flags, u32 nlmsg_pid,
			  struct netlink_ext_ack *extack)
{
	bool ext_learn_change = false;
	u8 old;
	int err;
	int notify = 0;
	struct net_device *dev;
	int update_isrouter = 0;

	trace_neigh_update(neigh, lladdr, new, flags, nlmsg_pid);

	write_lock_bh(&neigh->lock);

	dev    = neigh->dev;
	old    = neigh->nud_state;
	err    = -EPERM;

	if (!(flags & NEIGH_UPDATE_F_ADMIN) &&
	    (old & (NUD_NOARP | NUD_PERMANENT)))
		goto out;
	if (neigh->dead) {
		NL_SET_ERR_MSG(extack, "Neighbor entry is now dead");
		goto out;
	}

	ext_learn_change = neigh_update_ext_learned(neigh, flags, &notify);

	if (!(new & NUD_VALID)) {
		neigh_del_timer(neigh);
		if (old & NUD_CONNECTED)
			neigh_suspect(neigh);
		neigh->nud_state = new;
		err = 0;
		notify = old & NUD_VALID;
		if ((old & (NUD_INCOMPLETE | NUD_PROBE)) &&
		    (new & NUD_FAILED)) {
			neigh_invalidate(neigh);
			notify = 1;
		}
		goto out;
	}

	/* Compare new lladdr with cached one */
	if (!dev->addr_len) {
		/* First case: device needs no address. */
		lladdr = neigh->ha;
	} else if (lladdr) {
		/* The second case: if something is already cached
		   and a new address is proposed:
		   - compare new & old
		   - if they are different, check override flag
		 */
		if ((old & NUD_VALID) &&
		    !memcmp(lladdr, neigh->ha, dev->addr_len))
			lladdr = neigh->ha;
	} else {
		/* No address is supplied; if we know something,
		   use it, otherwise discard the request.
		 */
		err = -EINVAL;
		if (!(old & NUD_VALID)) {
			NL_SET_ERR_MSG(extack, "No link layer address given");
			goto out;
		}
		lladdr = neigh->ha;
	}

	/* Update confirmed timestamp for neighbour entry after we
	 * received ARP packet even if it doesn't change IP to MAC binding.
	 */
	if (new & NUD_CONNECTED)
		neigh->confirmed = jiffies;

	/* If entry was valid and address is not changed,
	   do not change entry state, if new one is STALE.
	 */
	err = 0;
	update_isrouter = flags & NEIGH_UPDATE_F_OVERRIDE_ISROUTER;
	if (old & NUD_VALID) {
		if (lladdr != neigh->ha && !(flags & NEIGH_UPDATE_F_OVERRIDE)) {
			update_isrouter = 0;
			if ((flags & NEIGH_UPDATE_F_WEAK_OVERRIDE) &&
			    (old & NUD_CONNECTED)) {
				lladdr = neigh->ha;
				new = NUD_STALE;
			} else
				goto out;
		} else {
			if (lladdr == neigh->ha && new == NUD_STALE &&
			    !(flags & NEIGH_UPDATE_F_ADMIN))
				new = old;
		}
	}

	/* Update timestamp only once we know we will make a change to the
	 * neighbour entry. Otherwise we risk to move the locktime window with
	 * noop updates and ignore relevant ARP updates.
	 */
	if (new != old || lladdr != neigh->ha)
		neigh->updated = jiffies;

	if (new != old) {
		neigh_del_timer(neigh);
		if (new & NUD_PROBE)
			atomic_set(&neigh->probes, 0);
		if (new & NUD_IN_TIMER)
			neigh_add_timer(neigh, (jiffies +
						((new & NUD_REACHABLE) ?
						 neigh->parms->reachable_time :
						 0)));
		neigh->nud_state = new;
		notify = 1;
	}

	if (lladdr != neigh->ha) {
		write_seqlock(&neigh->ha_lock);
		memcpy(&neigh->ha, lladdr, dev->addr_len);
		write_sequnlock(&neigh->ha_lock);
		neigh_update_hhs(neigh);
		if (!(new & NUD_CONNECTED))
			neigh->confirmed = jiffies -
				      (NEIGH_VAR(neigh->parms, BASE_REACHABLE_TIME) << 1);
		notify = 1;
	}
	if (new == old)
		goto out;
	if (new & NUD_CONNECTED)
		neigh_connect(neigh);
	else
		neigh_suspect(neigh);
	if (!(old & NUD_VALID)) {
		struct sk_buff *skb;

		/* Again: avoid dead loop if something went wrong */

		while (neigh->nud_state & NUD_VALID &&
		       (skb = __skb_dequeue(&neigh->arp_queue)) != NULL) {
			struct dst_entry *dst = skb_dst(skb);
			struct neighbour *n2, *n1 = neigh;
			write_unlock_bh(&neigh->lock);

			rcu_read_lock();

			/* Why not just use 'neigh' as-is?  The problem is that
			 * things such as shaper, eql, and sch_teql can end up
			 * using alternative, different, neigh objects to output
			 * the packet in the output path.  So what we need to do
			 * here is re-lookup the top-level neigh in the path so
			 * we can reinject the packet there.
			 */
			n2 = NULL;
			if (dst) {
				n2 = dst_neigh_lookup_skb(dst, skb);
				if (n2)
					n1 = n2;
			}
			n1->output(n1, skb);
			if (n2)
				neigh_release(n2);
			rcu_read_unlock();

			write_lock_bh(&neigh->lock);
		}
		__skb_queue_purge(&neigh->arp_queue);
		neigh->arp_queue_len_bytes = 0;
	}
out:
	if (update_isrouter)
		neigh_update_is_router(neigh, flags, &notify);
	write_unlock_bh(&neigh->lock);

	if (((new ^ old) & NUD_PERMANENT) || ext_learn_change)
		neigh_update_gc_list(neigh);

	if (notify)
		neigh_update_notify(neigh, nlmsg_pid);

	trace_neigh_update_done(neigh, err);

	return err;
}