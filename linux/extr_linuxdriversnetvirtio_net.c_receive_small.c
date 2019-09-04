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
typedef  int u32 ;
typedef  int u16 ;
struct xdp_frame {int dummy; } ;
struct xdp_buff {void* data_hard_start; void* data; void* data_end; int /*<<< orphan*/ * rxq; } ;
struct virtnet_rq_stats {unsigned int bytes; int /*<<< orphan*/  drops; int /*<<< orphan*/  xdp_drops; int /*<<< orphan*/  xdp_redirects; int /*<<< orphan*/  xdp_tx; int /*<<< orphan*/  xdp_packets; } ;
struct virtnet_info {unsigned int hdr_len; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int gso_type; } ;
struct virtio_net_hdr_mrg_rxbuf {TYPE_1__ hdr; } ;
struct skb_shared_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct receive_queue {int /*<<< orphan*/  xdp_rxq; int /*<<< orphan*/  xdp_prog; } ;
struct page {int dummy; } ;
struct net_device {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 unsigned int GOOD_PACKET_LEN ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 unsigned int VIRTIO_XDP_REDIR ; 
 unsigned int VIRTIO_XDP_TX ; 
 unsigned int VIRTNET_RX_PAD ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 struct sk_buff* build_skb (void*,unsigned int) ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct bpf_prog* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_vnet_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void*) ; 
 unsigned int virtnet_get_headroom (struct virtnet_info*) ; 
 int virtnet_xdp_xmit (struct net_device*,int,struct xdp_frame**,int /*<<< orphan*/ ) ; 
 int xdp_do_redirect (struct net_device*,struct xdp_buff*,struct bpf_prog*) ; 
 struct page* xdp_linearize_page (struct receive_queue*,int*,struct page*,int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  xdp_set_data_meta_invalid (struct xdp_buff*) ; 

__attribute__((used)) static struct sk_buff *receive_small(struct net_device *dev,
				     struct virtnet_info *vi,
				     struct receive_queue *rq,
				     void *buf, void *ctx,
				     unsigned int len,
				     unsigned int *xdp_xmit,
				     struct virtnet_rq_stats *stats)
{
	struct sk_buff *skb;
	struct bpf_prog *xdp_prog;
	unsigned int xdp_headroom = (unsigned long)ctx;
	unsigned int header_offset = VIRTNET_RX_PAD + xdp_headroom;
	unsigned int headroom = vi->hdr_len + header_offset;
	unsigned int buflen = SKB_DATA_ALIGN(GOOD_PACKET_LEN + headroom) +
			      SKB_DATA_ALIGN(sizeof(struct skb_shared_info));
	struct page *page = virt_to_head_page(buf);
	unsigned int delta = 0;
	struct page *xdp_page;
	int err;

	len -= vi->hdr_len;
	stats->bytes += len;

	rcu_read_lock();
	xdp_prog = rcu_dereference(rq->xdp_prog);
	if (xdp_prog) {
		struct virtio_net_hdr_mrg_rxbuf *hdr = buf + header_offset;
		struct xdp_frame *xdpf;
		struct xdp_buff xdp;
		void *orig_data;
		u32 act;

		if (unlikely(hdr->hdr.gso_type))
			goto err_xdp;

		if (unlikely(xdp_headroom < virtnet_get_headroom(vi))) {
			int offset = buf - page_address(page) + header_offset;
			unsigned int tlen = len + vi->hdr_len;
			u16 num_buf = 1;

			xdp_headroom = virtnet_get_headroom(vi);
			header_offset = VIRTNET_RX_PAD + xdp_headroom;
			headroom = vi->hdr_len + header_offset;
			buflen = SKB_DATA_ALIGN(GOOD_PACKET_LEN + headroom) +
				 SKB_DATA_ALIGN(sizeof(struct skb_shared_info));
			xdp_page = xdp_linearize_page(rq, &num_buf, page,
						      offset, header_offset,
						      &tlen);
			if (!xdp_page)
				goto err_xdp;

			buf = page_address(xdp_page);
			put_page(page);
			page = xdp_page;
		}

		xdp.data_hard_start = buf + VIRTNET_RX_PAD + vi->hdr_len;
		xdp.data = xdp.data_hard_start + xdp_headroom;
		xdp_set_data_meta_invalid(&xdp);
		xdp.data_end = xdp.data + len;
		xdp.rxq = &rq->xdp_rxq;
		orig_data = xdp.data;
		act = bpf_prog_run_xdp(xdp_prog, &xdp);
		stats->xdp_packets++;

		switch (act) {
		case XDP_PASS:
			/* Recalculate length in case bpf program changed it */
			delta = orig_data - xdp.data;
			len = xdp.data_end - xdp.data;
			break;
		case XDP_TX:
			stats->xdp_tx++;
			xdpf = convert_to_xdp_frame(&xdp);
			if (unlikely(!xdpf))
				goto err_xdp;
			err = virtnet_xdp_xmit(dev, 1, &xdpf, 0);
			if (unlikely(err < 0)) {
				trace_xdp_exception(vi->dev, xdp_prog, act);
				goto err_xdp;
			}
			*xdp_xmit |= VIRTIO_XDP_TX;
			rcu_read_unlock();
			goto xdp_xmit;
		case XDP_REDIRECT:
			stats->xdp_redirects++;
			err = xdp_do_redirect(dev, &xdp, xdp_prog);
			if (err)
				goto err_xdp;
			*xdp_xmit |= VIRTIO_XDP_REDIR;
			rcu_read_unlock();
			goto xdp_xmit;
		default:
			bpf_warn_invalid_xdp_action(act);
			/* fall through */
		case XDP_ABORTED:
			trace_xdp_exception(vi->dev, xdp_prog, act);
		case XDP_DROP:
			goto err_xdp;
		}
	}
	rcu_read_unlock();

	skb = build_skb(buf, buflen);
	if (!skb) {
		put_page(page);
		goto err;
	}
	skb_reserve(skb, headroom - delta);
	skb_put(skb, len);
	if (!delta) {
		buf += header_offset;
		memcpy(skb_vnet_hdr(skb), buf, vi->hdr_len);
	} /* keep zeroed vnet hdr since packet was changed by bpf */

err:
	return skb;

err_xdp:
	rcu_read_unlock();
	stats->xdp_drops++;
	stats->drops++;
	put_page(page);
xdp_xmit:
	return NULL;
}