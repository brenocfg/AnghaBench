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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  namedq; int /*<<< orphan*/  link; } ;
struct tipc_node {scalar_t__ signature; int link_cnt; scalar_t__ state; int /*<<< orphan*/  timer; int /*<<< orphan*/  keepalive_intv; TYPE_1__ bc_entry; int /*<<< orphan*/  net; int /*<<< orphan*/  capabilities; struct tipc_link_entry* links; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_link_entry {int /*<<< orphan*/  maddr; struct tipc_link* link; int /*<<< orphan*/  inputq; } ;
struct tipc_link {int dummy; } ;
struct tipc_bearer {size_t identity; int /*<<< orphan*/  window; int /*<<< orphan*/  priority; int /*<<< orphan*/  mtu; int /*<<< orphan*/  net_plane; int /*<<< orphan*/  tolerance; int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_FAILOVER_BEGIN_EVT ; 
 int /*<<< orphan*/  LINK_RESET_EVT ; 
 scalar_t__ NODE_FAILINGOVER ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct tipc_media_addr*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tipc_media_addr*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  tipc_bc_sndlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_create (struct net*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tipc_link**) ; 
 int /*<<< orphan*/  tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_is_reset (struct tipc_link*) ; 
 scalar_t__ tipc_link_is_up (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_reset (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_node_calculate_timer (struct tipc_node*,struct tipc_link*) ; 
 struct tipc_node* tipc_node_create (struct net*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_get (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_link_down (struct tipc_node*,size_t,int) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 int /*<<< orphan*/  trace_tipc_link_reset (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 

void tipc_node_check_dest(struct net *net, u32 addr,
			  u8 *peer_id, struct tipc_bearer *b,
			  u16 capabilities, u32 signature,
			  struct tipc_media_addr *maddr,
			  bool *respond, bool *dupl_addr)
{
	struct tipc_node *n;
	struct tipc_link *l;
	struct tipc_link_entry *le;
	bool addr_match = false;
	bool sign_match = false;
	bool link_up = false;
	bool accept_addr = false;
	bool reset = true;
	char *if_name;
	unsigned long intv;
	u16 session;

	*dupl_addr = false;
	*respond = false;

	n = tipc_node_create(net, addr, peer_id, capabilities);
	if (!n)
		return;

	tipc_node_write_lock(n);

	le = &n->links[b->identity];

	/* Prepare to validate requesting node's signature and media address */
	l = le->link;
	link_up = l && tipc_link_is_up(l);
	addr_match = l && !memcmp(&le->maddr, maddr, sizeof(*maddr));
	sign_match = (signature == n->signature);

	/* These three flags give us eight permutations: */

	if (sign_match && addr_match && link_up) {
		/* All is fine. Do nothing. */
		reset = false;
	} else if (sign_match && addr_match && !link_up) {
		/* Respond. The link will come up in due time */
		*respond = true;
	} else if (sign_match && !addr_match && link_up) {
		/* Peer has changed i/f address without rebooting.
		 * If so, the link will reset soon, and the next
		 * discovery will be accepted. So we can ignore it.
		 * It may also be an cloned or malicious peer having
		 * chosen the same node address and signature as an
		 * existing one.
		 * Ignore requests until the link goes down, if ever.
		 */
		*dupl_addr = true;
	} else if (sign_match && !addr_match && !link_up) {
		/* Peer link has changed i/f address without rebooting.
		 * It may also be a cloned or malicious peer; we can't
		 * distinguish between the two.
		 * The signature is correct, so we must accept.
		 */
		accept_addr = true;
		*respond = true;
	} else if (!sign_match && addr_match && link_up) {
		/* Peer node rebooted. Two possibilities:
		 *  - Delayed re-discovery; this link endpoint has already
		 *    reset and re-established contact with the peer, before
		 *    receiving a discovery message from that node.
		 *    (The peer happened to receive one from this node first).
		 *  - The peer came back so fast that our side has not
		 *    discovered it yet. Probing from this side will soon
		 *    reset the link, since there can be no working link
		 *    endpoint at the peer end, and the link will re-establish.
		 *  Accept the signature, since it comes from a known peer.
		 */
		n->signature = signature;
	} else if (!sign_match && addr_match && !link_up) {
		/*  The peer node has rebooted.
		 *  Accept signature, since it is a known peer.
		 */
		n->signature = signature;
		*respond = true;
	} else if (!sign_match && !addr_match && link_up) {
		/* Peer rebooted with new address, or a new/duplicate peer.
		 * Ignore until the link goes down, if ever.
		 */
		*dupl_addr = true;
	} else if (!sign_match && !addr_match && !link_up) {
		/* Peer rebooted with new address, or it is a new peer.
		 * Accept signature and address.
		 */
		n->signature = signature;
		accept_addr = true;
		*respond = true;
	}

	if (!accept_addr)
		goto exit;

	/* Now create new link if not already existing */
	if (!l) {
		if (n->link_cnt == 2)
			goto exit;

		if_name = strchr(b->name, ':') + 1;
		get_random_bytes(&session, sizeof(u16));
		if (!tipc_link_create(net, if_name, b->identity, b->tolerance,
				      b->net_plane, b->mtu, b->priority,
				      b->window, session,
				      tipc_own_addr(net), addr, peer_id,
				      n->capabilities,
				      tipc_bc_sndlink(n->net), n->bc_entry.link,
				      &le->inputq,
				      &n->bc_entry.namedq, &l)) {
			*respond = false;
			goto exit;
		}
		trace_tipc_link_reset(l, TIPC_DUMP_ALL, "link created!");
		tipc_link_reset(l);
		tipc_link_fsm_evt(l, LINK_RESET_EVT);
		if (n->state == NODE_FAILINGOVER)
			tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
		le->link = l;
		n->link_cnt++;
		tipc_node_calculate_timer(n, l);
		if (n->link_cnt == 1) {
			intv = jiffies + msecs_to_jiffies(n->keepalive_intv);
			if (!mod_timer(&n->timer, intv))
				tipc_node_get(n);
		}
	}
	memcpy(&le->maddr, maddr, sizeof(*maddr));
exit:
	tipc_node_write_unlock(n);
	if (reset && l && !tipc_link_is_reset(l))
		tipc_node_link_down(n, b->identity, false);
	tipc_node_put(n);
}