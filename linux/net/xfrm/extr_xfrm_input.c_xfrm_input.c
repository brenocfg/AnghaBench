#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_20__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state_afinfo {int (* transport_finish ) (struct sk_buff*,int) ;} ;
struct xfrm_mode {int /*<<< orphan*/  family; } ;
struct TYPE_25__ {unsigned int family; int flags; } ;
struct TYPE_23__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_22__ {unsigned int family; } ;
struct TYPE_42__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_29__ {int /*<<< orphan*/  integrity_failed; } ;
struct TYPE_24__ {scalar_t__ state; } ;
struct xfrm_state {TYPE_16__* type; int /*<<< orphan*/  lock; struct xfrm_mode inner_mode; TYPE_13__ outer_mode; TYPE_11__ id; TYPE_10__ sel; TYPE_9__ curlft; TYPE_8__* repl; TYPE_17__ stats; TYPE_7__* type_offload; TYPE_6__* encap; TYPE_12__ km; } ;
struct xfrm_offload {int flags; int status; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; int /*<<< orphan*/  mark; } ;
struct sec_path {scalar_t__ len; scalar_t__ olen; struct xfrm_state** xvec; } ;
struct net {int dummy; } ;
typedef  void* __be32 ;
struct TYPE_41__ {int /*<<< orphan*/  (* advance ) (struct xfrm_state*,void*) ;scalar_t__ (* recheck ) (struct xfrm_state*,struct sk_buff*,void*) ;scalar_t__ (* check ) (struct xfrm_state*,struct sk_buff*,void*) ;} ;
struct TYPE_40__ {int (* input_tail ) (struct xfrm_state*,struct sk_buff*) ;} ;
struct TYPE_39__ {int encap_type; } ;
struct TYPE_38__ {TYPE_4__* ip6; TYPE_2__* ip4; } ;
struct TYPE_36__ {int /*<<< orphan*/  i_key; } ;
struct TYPE_37__ {TYPE_3__ parms; } ;
struct TYPE_32__ {int /*<<< orphan*/  i_key; } ;
struct TYPE_35__ {TYPE_1__ parms; } ;
struct TYPE_34__ {int protocol; } ;
struct TYPE_26__ {void* hi; void* low; } ;
struct TYPE_27__ {TYPE_14__ input; } ;
struct TYPE_33__ {TYPE_15__ seq; } ;
struct TYPE_31__ {unsigned int family; scalar_t__ daddroff; void* seq; } ;
struct TYPE_30__ {TYPE_5__ tunnel; } ;
struct TYPE_28__ {int proto; int (* input ) (struct xfrm_state*,struct sk_buff*) ;} ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int AF_UNSPEC ; 
 int CRYPTO_DONE ; 
 int CRYPTO_INVALID_PROTOCOL ; 
 int CRYPTO_SUCCESS ; 
 int CRYPTO_TRANSPORT_AH_AUTH_FAILED ; 
 int CRYPTO_TRANSPORT_ESP_AUTH_FAILED ; 
 int CRYPTO_TUNNEL_AH_AUTH_FAILED ; 
 int CRYPTO_TUNNEL_ESP_AUTH_FAILED ; 
 int EAFNOSUPPORT ; 
 int EBADMSG ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMACQUIREERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINBUFFERERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINHDRERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINNOSTATES ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEEXPIRED ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEINVALID ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEMISMATCH ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEMODEERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEPROTOERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATESEQERROR ; 
 int XFRM_GRO ; 
 int /*<<< orphan*/  XFRM_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFRM_MAX_DEPTH ; 
 int XFRM_MODE_FLAG_TUNNEL ; 
 TYPE_21__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 TYPE_20__* XFRM_SKB_CB (struct sk_buff*) ; 
 TYPE_19__* XFRM_SPI_SKB_CB (struct sk_buff*) ; 
 scalar_t__ XFRM_STATE_ACQ ; 
 scalar_t__ XFRM_STATE_VALID ; 
 TYPE_18__* XFRM_TUNNEL_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gro_cells ; 
 int /*<<< orphan*/  gro_cells_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (struct xfrm_state_afinfo const*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 struct sec_path* secpath_set (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_force (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 struct sec_path* skb_sec_path (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct xfrm_state*,struct sk_buff*,void*) ; 
 int stub2 (struct xfrm_state*,struct sk_buff*) ; 
 int stub3 (struct xfrm_state*,struct sk_buff*) ; 
 scalar_t__ stub4 (struct xfrm_state*,struct sk_buff*,void*) ; 
 int /*<<< orphan*/  stub5 (struct xfrm_state*,void*) ; 
 int stub6 (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm_audit_state_icvfail (struct xfrm_state*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  xfrm_audit_state_notfound (struct sk_buff*,unsigned int,void*,void*) ; 
 scalar_t__ xfrm_inner_mode_input (struct xfrm_state*,struct xfrm_mode const*,struct sk_buff*) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 
 struct xfrm_mode* xfrm_ip2inner_mode (struct xfrm_state*,int) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 
 int xfrm_parse_spi (struct sk_buff*,int,void**,void**) ; 
 int xfrm_rcv_cb (struct sk_buff*,unsigned int,int,int) ; 
 int /*<<< orphan*/  xfrm_replay_seqhi (struct xfrm_state*,void*) ; 
 int /*<<< orphan*/  xfrm_smark_get (int /*<<< orphan*/ ,struct xfrm_state*) ; 
 struct xfrm_state_afinfo* xfrm_state_afinfo_get_rcu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_state_check_expire (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,unsigned int) ; 
 scalar_t__ xfrm_tunnel_check (struct sk_buff*,struct xfrm_state*,unsigned int) ; 

int xfrm_input(struct sk_buff *skb, int nexthdr, __be32 spi, int encap_type)
{
	const struct xfrm_state_afinfo *afinfo;
	struct net *net = dev_net(skb->dev);
	const struct xfrm_mode *inner_mode;
	int err;
	__be32 seq;
	__be32 seq_hi;
	struct xfrm_state *x = NULL;
	xfrm_address_t *daddr;
	u32 mark = skb->mark;
	unsigned int family = AF_UNSPEC;
	int decaps = 0;
	int async = 0;
	bool xfrm_gro = false;
	bool crypto_done = false;
	struct xfrm_offload *xo = xfrm_offload(skb);
	struct sec_path *sp;

	if (encap_type < 0) {
		x = xfrm_input_state(skb);

		if (unlikely(x->km.state != XFRM_STATE_VALID)) {
			if (x->km.state == XFRM_STATE_ACQ)
				XFRM_INC_STATS(net, LINUX_MIB_XFRMACQUIREERROR);
			else
				XFRM_INC_STATS(net,
					       LINUX_MIB_XFRMINSTATEINVALID);
			goto drop;
		}

		family = x->outer_mode.family;

		/* An encap_type of -1 indicates async resumption. */
		if (encap_type == -1) {
			async = 1;
			seq = XFRM_SKB_CB(skb)->seq.input.low;
			goto resume;
		}

		/* encap_type < -1 indicates a GRO call. */
		encap_type = 0;
		seq = XFRM_SPI_SKB_CB(skb)->seq;

		if (xo && (xo->flags & CRYPTO_DONE)) {
			crypto_done = true;
			family = XFRM_SPI_SKB_CB(skb)->family;

			if (!(xo->status & CRYPTO_SUCCESS)) {
				if (xo->status &
				    (CRYPTO_TRANSPORT_AH_AUTH_FAILED |
				     CRYPTO_TRANSPORT_ESP_AUTH_FAILED |
				     CRYPTO_TUNNEL_AH_AUTH_FAILED |
				     CRYPTO_TUNNEL_ESP_AUTH_FAILED)) {

					xfrm_audit_state_icvfail(x, skb,
								 x->type->proto);
					x->stats.integrity_failed++;
					XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEPROTOERROR);
					goto drop;
				}

				if (xo->status & CRYPTO_INVALID_PROTOCOL) {
					XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEPROTOERROR);
					goto drop;
				}

				XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
				goto drop;
			}

			if ((err = xfrm_parse_spi(skb, nexthdr, &spi, &seq)) != 0) {
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
				goto drop;
			}
		}

		goto lock;
	}

	family = XFRM_SPI_SKB_CB(skb)->family;

	/* if tunnel is present override skb->mark value with tunnel i_key */
	switch (family) {
	case AF_INET:
		if (XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4)
			mark = be32_to_cpu(XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4->parms.i_key);
		break;
	case AF_INET6:
		if (XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6)
			mark = be32_to_cpu(XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6->parms.i_key);
		break;
	}

	sp = secpath_set(skb);
	if (!sp) {
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINERROR);
		goto drop;
	}

	seq = 0;
	if (!spi && (err = xfrm_parse_spi(skb, nexthdr, &spi, &seq)) != 0) {
		secpath_reset(skb);
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
		goto drop;
	}

	daddr = (xfrm_address_t *)(skb_network_header(skb) +
				   XFRM_SPI_SKB_CB(skb)->daddroff);
	do {
		sp = skb_sec_path(skb);

		if (sp->len == XFRM_MAX_DEPTH) {
			secpath_reset(skb);
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
			goto drop;
		}

		x = xfrm_state_lookup(net, mark, daddr, spi, nexthdr, family);
		if (x == NULL) {
			secpath_reset(skb);
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINNOSTATES);
			xfrm_audit_state_notfound(skb, family, spi, seq);
			goto drop;
		}

		skb->mark = xfrm_smark_get(skb->mark, x);

		sp->xvec[sp->len++] = x;

		skb_dst_force(skb);
		if (!skb_dst(skb)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINERROR);
			goto drop;
		}

lock:
		spin_lock(&x->lock);

		if (unlikely(x->km.state != XFRM_STATE_VALID)) {
			if (x->km.state == XFRM_STATE_ACQ)
				XFRM_INC_STATS(net, LINUX_MIB_XFRMACQUIREERROR);
			else
				XFRM_INC_STATS(net,
					       LINUX_MIB_XFRMINSTATEINVALID);
			goto drop_unlock;
		}

		if ((x->encap ? x->encap->encap_type : 0) != encap_type) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMISMATCH);
			goto drop_unlock;
		}

		if (x->repl->check(x, skb, seq)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATESEQERROR);
			goto drop_unlock;
		}

		if (xfrm_state_check_expire(x)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEEXPIRED);
			goto drop_unlock;
		}

		spin_unlock(&x->lock);

		if (xfrm_tunnel_check(skb, x, family)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMODEERROR);
			goto drop;
		}

		seq_hi = htonl(xfrm_replay_seqhi(x, seq));

		XFRM_SKB_CB(skb)->seq.input.low = seq;
		XFRM_SKB_CB(skb)->seq.input.hi = seq_hi;

		dev_hold(skb->dev);

		if (crypto_done)
			nexthdr = x->type_offload->input_tail(x, skb);
		else
			nexthdr = x->type->input(x, skb);

		if (nexthdr == -EINPROGRESS)
			return 0;
resume:
		dev_put(skb->dev);

		spin_lock(&x->lock);
		if (nexthdr <= 0) {
			if (nexthdr == -EBADMSG) {
				xfrm_audit_state_icvfail(x, skb,
							 x->type->proto);
				x->stats.integrity_failed++;
			}
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEPROTOERROR);
			goto drop_unlock;
		}

		/* only the first xfrm gets the encap type */
		encap_type = 0;

		if (async && x->repl->recheck(x, skb, seq)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATESEQERROR);
			goto drop_unlock;
		}

		x->repl->advance(x, seq);

		x->curlft.bytes += skb->len;
		x->curlft.packets++;

		spin_unlock(&x->lock);

		XFRM_MODE_SKB_CB(skb)->protocol = nexthdr;

		inner_mode = &x->inner_mode;

		if (x->sel.family == AF_UNSPEC) {
			inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
			if (inner_mode == NULL) {
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMODEERROR);
				goto drop;
			}
		}

		if (xfrm_inner_mode_input(x, inner_mode, skb)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMODEERROR);
			goto drop;
		}

		if (x->outer_mode.flags & XFRM_MODE_FLAG_TUNNEL) {
			decaps = 1;
			break;
		}

		/*
		 * We need the inner address.  However, we only get here for
		 * transport mode so the outer address is identical.
		 */
		daddr = &x->id.daddr;
		family = x->outer_mode.family;

		err = xfrm_parse_spi(skb, nexthdr, &spi, &seq);
		if (err < 0) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
			goto drop;
		}
		crypto_done = false;
	} while (!err);

	err = xfrm_rcv_cb(skb, family, x->type->proto, 0);
	if (err)
		goto drop;

	nf_reset_ct(skb);

	if (decaps) {
		sp = skb_sec_path(skb);
		if (sp)
			sp->olen = 0;
		skb_dst_drop(skb);
		gro_cells_receive(&gro_cells, skb);
		return 0;
	} else {
		xo = xfrm_offload(skb);
		if (xo)
			xfrm_gro = xo->flags & XFRM_GRO;

		err = -EAFNOSUPPORT;
		rcu_read_lock();
		afinfo = xfrm_state_afinfo_get_rcu(x->inner_mode.family);
		if (likely(afinfo))
			err = afinfo->transport_finish(skb, xfrm_gro || async);
		rcu_read_unlock();
		if (xfrm_gro) {
			sp = skb_sec_path(skb);
			if (sp)
				sp->olen = 0;
			skb_dst_drop(skb);
			gro_cells_receive(&gro_cells, skb);
			return err;
		}

		return err;
	}

drop_unlock:
	spin_unlock(&x->lock);
drop:
	xfrm_rcv_cb(skb, family, x && x->type ? x->type->proto : nexthdr, -1);
	kfree_skb(skb);
	return 0;
}