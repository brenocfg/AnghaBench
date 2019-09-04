#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct tcphdr {scalar_t__ rst; scalar_t__ fin; scalar_t__ ack; scalar_t__ syn; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  seq; int /*<<< orphan*/  window; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nf_tcp_net {unsigned int* timeouts; scalar_t__ tcp_max_retrans; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct TYPE_7__ {int state; int last_dir; unsigned int last_index; void* last_end; scalar_t__ last_win; int last_wscale; int last_flags; scalar_t__ retrans; TYPE_4__* seen; void* last_seq; } ;
struct TYPE_6__ {TYPE_3__ tcp; } ;
struct nf_conn {int /*<<< orphan*/  status; int /*<<< orphan*/  lock; TYPE_2__ proto; TYPE_1__* tuplehash; } ;
struct net {int dummy; } ;
struct ip_ct_tcp_state {int flags; int td_scale; } ;
typedef  enum tcp_conntrack { ____Placeholder_tcp_conntrack } tcp_conntrack ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  int /*<<< orphan*/  _tcph ;
struct TYPE_8__ {int flags; void* td_end; void* td_maxend; int td_maxwin; int td_scale; void* td_maxack; } ;
struct TYPE_5__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  IPCT_ASSURED ; 
 int /*<<< orphan*/  IPCT_PROTOINFO ; 
 int /*<<< orphan*/  IPS_ASSURED_BIT ; 
 int /*<<< orphan*/  IPS_SEEN_REPLY_BIT ; 
 int IP_CT_DIR_ORIGINAL ; 
 int IP_CT_DIR_REPLY ; 
 int IP_CT_EXP_CHALLENGE_ACK ; 
 int IP_CT_TCP_FLAG_CLOSE_INIT ; 
 int IP_CT_TCP_FLAG_DATA_UNACKNOWLEDGED ; 
 int IP_CT_TCP_FLAG_MAXACK_SET ; 
 int IP_CT_TCP_FLAG_SACK_PERM ; 
 int IP_CT_TCP_FLAG_WINDOW_SCALE ; 
 int IP_CT_TCP_SIMULTANEOUS_OPEN ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int NF_REPEAT ; 
 unsigned int TCP_ACK_SET ; 
#define  TCP_CONNTRACK_CLOSE 134 
 int TCP_CONNTRACK_ESTABLISHED ; 
 int TCP_CONNTRACK_FIN_WAIT ; 
#define  TCP_CONNTRACK_IGNORE 133 
 int TCP_CONNTRACK_LAST_ACK ; 
#define  TCP_CONNTRACK_MAX 132 
 size_t TCP_CONNTRACK_RETRANS ; 
#define  TCP_CONNTRACK_SYN_RECV 131 
#define  TCP_CONNTRACK_SYN_SENT 130 
#define  TCP_CONNTRACK_SYN_SENT2 129 
#define  TCP_CONNTRACK_TIME_WAIT 128 
 size_t TCP_CONNTRACK_UNACK ; 
 unsigned int TCP_RST_SET ; 
 unsigned int TCP_SYNACK_SET ; 
 unsigned int TCP_SYN_SET ; 
 int /*<<< orphan*/  before (void*,void*) ; 
 unsigned int get_conntrack_index (struct tcphdr const*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_conntrack_tcp_established (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_kill (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_kill_acct (struct nf_conn*,int,struct sk_buff const*) ; 
 int /*<<< orphan*/  nf_ct_l4proto_log_invalid (struct sk_buff const*,struct nf_conn*,char*,...) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff const*,unsigned long) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 
 int /*<<< orphan*/  nfct_synproxy (struct nf_conn*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 void* segment_seq_plus_len (void*,int /*<<< orphan*/ ,unsigned int,struct tcphdr const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct tcphdr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcp_conntrack_names ; 
 int*** tcp_conntracks ; 
 int /*<<< orphan*/  tcp_in_window (struct nf_conn*,TYPE_3__*,int,unsigned int,struct sk_buff const*,unsigned int,struct tcphdr const*) ; 
 int /*<<< orphan*/  tcp_options (struct sk_buff const*,unsigned int,struct tcphdr const*,struct ip_ct_tcp_state*) ; 
 struct nf_tcp_net* tcp_pernet (struct net*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcp_packet(struct nf_conn *ct,
		      const struct sk_buff *skb,
		      unsigned int dataoff,
		      enum ip_conntrack_info ctinfo)
{
	struct net *net = nf_ct_net(ct);
	struct nf_tcp_net *tn = tcp_pernet(net);
	struct nf_conntrack_tuple *tuple;
	enum tcp_conntrack new_state, old_state;
	unsigned int index, *timeouts;
	enum ip_conntrack_dir dir;
	const struct tcphdr *th;
	struct tcphdr _tcph;
	unsigned long timeout;

	th = skb_header_pointer(skb, dataoff, sizeof(_tcph), &_tcph);
	BUG_ON(th == NULL);

	spin_lock_bh(&ct->lock);
	old_state = ct->proto.tcp.state;
	dir = CTINFO2DIR(ctinfo);
	index = get_conntrack_index(th);
	new_state = tcp_conntracks[dir][index][old_state];
	tuple = &ct->tuplehash[dir].tuple;

	switch (new_state) {
	case TCP_CONNTRACK_SYN_SENT:
		if (old_state < TCP_CONNTRACK_TIME_WAIT)
			break;
		/* RFC 1122: "When a connection is closed actively,
		 * it MUST linger in TIME-WAIT state for a time 2xMSL
		 * (Maximum Segment Lifetime). However, it MAY accept
		 * a new SYN from the remote TCP to reopen the connection
		 * directly from TIME-WAIT state, if..."
		 * We ignore the conditions because we are in the
		 * TIME-WAIT state anyway.
		 *
		 * Handle aborted connections: we and the server
		 * think there is an existing connection but the client
		 * aborts it and starts a new one.
		 */
		if (((ct->proto.tcp.seen[dir].flags
		      | ct->proto.tcp.seen[!dir].flags)
		     & IP_CT_TCP_FLAG_CLOSE_INIT)
		    || (ct->proto.tcp.last_dir == dir
		        && ct->proto.tcp.last_index == TCP_RST_SET)) {
			/* Attempt to reopen a closed/aborted connection.
			 * Delete this connection and look up again. */
			spin_unlock_bh(&ct->lock);

			/* Only repeat if we can actually remove the timer.
			 * Destruction may already be in progress in process
			 * context and we must give it a chance to terminate.
			 */
			if (nf_ct_kill(ct))
				return -NF_REPEAT;
			return NF_DROP;
		}
		/* Fall through */
	case TCP_CONNTRACK_IGNORE:
		/* Ignored packets:
		 *
		 * Our connection entry may be out of sync, so ignore
		 * packets which may signal the real connection between
		 * the client and the server.
		 *
		 * a) SYN in ORIGINAL
		 * b) SYN/ACK in REPLY
		 * c) ACK in reply direction after initial SYN in original.
		 *
		 * If the ignored packet is invalid, the receiver will send
		 * a RST we'll catch below.
		 */
		if (index == TCP_SYNACK_SET
		    && ct->proto.tcp.last_index == TCP_SYN_SET
		    && ct->proto.tcp.last_dir != dir
		    && ntohl(th->ack_seq) == ct->proto.tcp.last_end) {
			/* b) This SYN/ACK acknowledges a SYN that we earlier
			 * ignored as invalid. This means that the client and
			 * the server are both in sync, while the firewall is
			 * not. We get in sync from the previously annotated
			 * values.
			 */
			old_state = TCP_CONNTRACK_SYN_SENT;
			new_state = TCP_CONNTRACK_SYN_RECV;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_end =
				ct->proto.tcp.last_end;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_maxend =
				ct->proto.tcp.last_end;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_maxwin =
				ct->proto.tcp.last_win == 0 ?
					1 : ct->proto.tcp.last_win;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_scale =
				ct->proto.tcp.last_wscale;
			ct->proto.tcp.last_flags &= ~IP_CT_EXP_CHALLENGE_ACK;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].flags =
				ct->proto.tcp.last_flags;
			memset(&ct->proto.tcp.seen[dir], 0,
			       sizeof(struct ip_ct_tcp_state));
			break;
		}
		ct->proto.tcp.last_index = index;
		ct->proto.tcp.last_dir = dir;
		ct->proto.tcp.last_seq = ntohl(th->seq);
		ct->proto.tcp.last_end =
		    segment_seq_plus_len(ntohl(th->seq), skb->len, dataoff, th);
		ct->proto.tcp.last_win = ntohs(th->window);

		/* a) This is a SYN in ORIGINAL. The client and the server
		 * may be in sync but we are not. In that case, we annotate
		 * the TCP options and let the packet go through. If it is a
		 * valid SYN packet, the server will reply with a SYN/ACK, and
		 * then we'll get in sync. Otherwise, the server potentially
		 * responds with a challenge ACK if implementing RFC5961.
		 */
		if (index == TCP_SYN_SET && dir == IP_CT_DIR_ORIGINAL) {
			struct ip_ct_tcp_state seen = {};

			ct->proto.tcp.last_flags =
			ct->proto.tcp.last_wscale = 0;
			tcp_options(skb, dataoff, th, &seen);
			if (seen.flags & IP_CT_TCP_FLAG_WINDOW_SCALE) {
				ct->proto.tcp.last_flags |=
					IP_CT_TCP_FLAG_WINDOW_SCALE;
				ct->proto.tcp.last_wscale = seen.td_scale;
			}
			if (seen.flags & IP_CT_TCP_FLAG_SACK_PERM) {
				ct->proto.tcp.last_flags |=
					IP_CT_TCP_FLAG_SACK_PERM;
			}
			/* Mark the potential for RFC5961 challenge ACK,
			 * this pose a special problem for LAST_ACK state
			 * as ACK is intrepretated as ACKing last FIN.
			 */
			if (old_state == TCP_CONNTRACK_LAST_ACK)
				ct->proto.tcp.last_flags |=
					IP_CT_EXP_CHALLENGE_ACK;
		}
		spin_unlock_bh(&ct->lock);
		nf_ct_l4proto_log_invalid(skb, ct, "invalid packet ignored in "
					  "state %s ", tcp_conntrack_names[old_state]);
		return NF_ACCEPT;
	case TCP_CONNTRACK_MAX:
		/* Special case for SYN proxy: when the SYN to the server or
		 * the SYN/ACK from the server is lost, the client may transmit
		 * a keep-alive packet while in SYN_SENT state. This needs to
		 * be associated with the original conntrack entry in order to
		 * generate a new SYN with the correct sequence number.
		 */
		if (nfct_synproxy(ct) && old_state == TCP_CONNTRACK_SYN_SENT &&
		    index == TCP_ACK_SET && dir == IP_CT_DIR_ORIGINAL &&
		    ct->proto.tcp.last_dir == IP_CT_DIR_ORIGINAL &&
		    ct->proto.tcp.seen[dir].td_end - 1 == ntohl(th->seq)) {
			pr_debug("nf_ct_tcp: SYN proxy client keep alive\n");
			spin_unlock_bh(&ct->lock);
			return NF_ACCEPT;
		}

		/* Invalid packet */
		pr_debug("nf_ct_tcp: Invalid dir=%i index=%u ostate=%u\n",
			 dir, get_conntrack_index(th), old_state);
		spin_unlock_bh(&ct->lock);
		nf_ct_l4proto_log_invalid(skb, ct, "invalid state");
		return -NF_ACCEPT;
	case TCP_CONNTRACK_TIME_WAIT:
		/* RFC5961 compliance cause stack to send "challenge-ACK"
		 * e.g. in response to spurious SYNs.  Conntrack MUST
		 * not believe this ACK is acking last FIN.
		 */
		if (old_state == TCP_CONNTRACK_LAST_ACK &&
		    index == TCP_ACK_SET &&
		    ct->proto.tcp.last_dir != dir &&
		    ct->proto.tcp.last_index == TCP_SYN_SET &&
		    (ct->proto.tcp.last_flags & IP_CT_EXP_CHALLENGE_ACK)) {
			/* Detected RFC5961 challenge ACK */
			ct->proto.tcp.last_flags &= ~IP_CT_EXP_CHALLENGE_ACK;
			spin_unlock_bh(&ct->lock);
			nf_ct_l4proto_log_invalid(skb, ct, "challenge-ack ignored");
			return NF_ACCEPT; /* Don't change state */
		}
		break;
	case TCP_CONNTRACK_SYN_SENT2:
		/* tcp_conntracks table is not smart enough to handle
		 * simultaneous open.
		 */
		ct->proto.tcp.last_flags |= IP_CT_TCP_SIMULTANEOUS_OPEN;
		break;
	case TCP_CONNTRACK_SYN_RECV:
		if (dir == IP_CT_DIR_REPLY && index == TCP_ACK_SET &&
		    ct->proto.tcp.last_flags & IP_CT_TCP_SIMULTANEOUS_OPEN)
			new_state = TCP_CONNTRACK_ESTABLISHED;
		break;
	case TCP_CONNTRACK_CLOSE:
		if (index != TCP_RST_SET)
			break;

		if (ct->proto.tcp.seen[!dir].flags & IP_CT_TCP_FLAG_MAXACK_SET) {
			u32 seq = ntohl(th->seq);

			if (before(seq, ct->proto.tcp.seen[!dir].td_maxack)) {
				/* Invalid RST  */
				spin_unlock_bh(&ct->lock);
				nf_ct_l4proto_log_invalid(skb, ct, "invalid rst");
				return -NF_ACCEPT;
			}

			if (!nf_conntrack_tcp_established(ct) ||
			    seq == ct->proto.tcp.seen[!dir].td_maxack)
				break;

			/* Check if rst is part of train, such as
			 *   foo:80 > bar:4379: P, 235946583:235946602(19) ack 42
			 *   foo:80 > bar:4379: R, 235946602:235946602(0)  ack 42
			 */
			if (ct->proto.tcp.last_index == TCP_ACK_SET &&
			    ct->proto.tcp.last_dir == dir &&
			    seq == ct->proto.tcp.last_end)
				break;

			/* ... RST sequence number doesn't match exactly, keep
			 * established state to allow a possible challenge ACK.
			 */
			new_state = old_state;
		}
		if (((test_bit(IPS_SEEN_REPLY_BIT, &ct->status)
			 && ct->proto.tcp.last_index == TCP_SYN_SET)
			|| (!test_bit(IPS_ASSURED_BIT, &ct->status)
			    && ct->proto.tcp.last_index == TCP_ACK_SET))
		    && ntohl(th->ack_seq) == ct->proto.tcp.last_end) {
			/* RST sent to invalid SYN or ACK we had let through
			 * at a) and c) above:
			 *
			 * a) SYN was in window then
			 * c) we hold a half-open connection.
			 *
			 * Delete our connection entry.
			 * We skip window checking, because packet might ACK
			 * segments we ignored. */
			goto in_window;
		}
		break;
	default:
		/* Keep compilers happy. */
		break;
	}

	if (!tcp_in_window(ct, &ct->proto.tcp, dir, index,
			   skb, dataoff, th)) {
		spin_unlock_bh(&ct->lock);
		return -NF_ACCEPT;
	}
     in_window:
	/* From now on we have got in-window packets */
	ct->proto.tcp.last_index = index;
	ct->proto.tcp.last_dir = dir;

	pr_debug("tcp_conntracks: ");
	nf_ct_dump_tuple(tuple);
	pr_debug("syn=%i ack=%i fin=%i rst=%i old=%i new=%i\n",
		 (th->syn ? 1 : 0), (th->ack ? 1 : 0),
		 (th->fin ? 1 : 0), (th->rst ? 1 : 0),
		 old_state, new_state);

	ct->proto.tcp.state = new_state;
	if (old_state != new_state
	    && new_state == TCP_CONNTRACK_FIN_WAIT)
		ct->proto.tcp.seen[dir].flags |= IP_CT_TCP_FLAG_CLOSE_INIT;

	timeouts = nf_ct_timeout_lookup(ct);
	if (!timeouts)
		timeouts = tn->timeouts;

	if (ct->proto.tcp.retrans >= tn->tcp_max_retrans &&
	    timeouts[new_state] > timeouts[TCP_CONNTRACK_RETRANS])
		timeout = timeouts[TCP_CONNTRACK_RETRANS];
	else if (unlikely(index == TCP_RST_SET))
		timeout = timeouts[TCP_CONNTRACK_CLOSE];
	else if ((ct->proto.tcp.seen[0].flags | ct->proto.tcp.seen[1].flags) &
		 IP_CT_TCP_FLAG_DATA_UNACKNOWLEDGED &&
		 timeouts[new_state] > timeouts[TCP_CONNTRACK_UNACK])
		timeout = timeouts[TCP_CONNTRACK_UNACK];
	else if (ct->proto.tcp.last_win == 0 &&
		 timeouts[new_state] > timeouts[TCP_CONNTRACK_RETRANS])
		timeout = timeouts[TCP_CONNTRACK_RETRANS];
	else
		timeout = timeouts[new_state];
	spin_unlock_bh(&ct->lock);

	if (new_state != old_state)
		nf_conntrack_event_cache(IPCT_PROTOINFO, ct);

	if (!test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) {
		/* If only reply is a RST, we can consider ourselves not to
		   have an established connection: this is a fairly common
		   problem case, so we can delete the conntrack
		   immediately.  --RR */
		if (th->rst) {
			nf_ct_kill_acct(ct, ctinfo, skb);
			return NF_ACCEPT;
		}
		/* ESTABLISHED without SEEN_REPLY, i.e. mid-connection
		 * pickup with loose=1. Avoid large ESTABLISHED timeout.
		 */
		if (new_state == TCP_CONNTRACK_ESTABLISHED &&
		    timeout > timeouts[TCP_CONNTRACK_UNACK])
			timeout = timeouts[TCP_CONNTRACK_UNACK];
	} else if (!test_bit(IPS_ASSURED_BIT, &ct->status)
		   && (old_state == TCP_CONNTRACK_SYN_RECV
		       || old_state == TCP_CONNTRACK_ESTABLISHED)
		   && new_state == TCP_CONNTRACK_ESTABLISHED) {
		/* Set ASSURED if we see see valid ack in ESTABLISHED
		   after SYN_RECV or a valid answer for a picked up
		   connection. */
		set_bit(IPS_ASSURED_BIT, &ct->status);
		nf_conntrack_event_cache(IPCT_ASSURED, ct);
	}
	nf_ct_refresh_acct(ct, ctinfo, skb, timeout);

	return NF_ACCEPT;
}