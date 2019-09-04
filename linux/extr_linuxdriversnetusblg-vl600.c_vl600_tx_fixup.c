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
typedef  int uint32_t ;
struct vl600_frame_hdr {void* pkt_cnt; void* serial; void* len; } ;
struct vl600_pkt_hdr {void* len; struct vl600_frame_hdr dummy; int /*<<< orphan*/  h_proto; } ;
struct usbnet {int dummy; } ;
struct sk_buff {int len; scalar_t__ data; scalar_t__ head; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (void**) ; 
 scalar_t__ memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct vl600_frame_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 struct vl600_frame_hdr* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *vl600_tx_fixup(struct usbnet *dev,
		struct sk_buff *skb, gfp_t flags)
{
	struct sk_buff *ret;
	struct vl600_frame_hdr *frame;
	struct vl600_pkt_hdr *packet;
	static uint32_t serial = 1;
	int orig_len = skb->len - sizeof(struct ethhdr);
	int full_len = (skb->len + sizeof(struct vl600_frame_hdr) + 3) & ~3;

	frame = (struct vl600_frame_hdr *) skb->data;
	if (skb->len > sizeof(*frame) && skb->len == le32_to_cpup(&frame->len))
		return skb; /* Already encapsulated? */

	if (skb->len < sizeof(struct ethhdr))
		/* Drop, device can only deal with ethernet packets */
		return NULL;

	if (!skb_cloned(skb)) {
		int headroom = skb_headroom(skb);
		int tailroom = skb_tailroom(skb);

		if (tailroom >= full_len - skb->len - sizeof(*frame) &&
				headroom >= sizeof(*frame))
			/* There's enough head and tail room */
			goto encapsulate;

		if (headroom + tailroom + skb->len >= full_len) {
			/* There's enough total room, just readjust */
			skb->data = memmove(skb->head + sizeof(*frame),
					skb->data, skb->len);
			skb_set_tail_pointer(skb, skb->len);
			goto encapsulate;
		}
	}

	/* Alloc a new skb with the required size */
	ret = skb_copy_expand(skb, sizeof(struct vl600_frame_hdr), full_len -
			skb->len - sizeof(struct vl600_frame_hdr), flags);
	dev_kfree_skb_any(skb);
	if (!ret)
		return ret;
	skb = ret;

encapsulate:
	/* Packet header is same size as ethernet packet header
	 * (sizeof(*packet) == sizeof(struct ethhdr)), additionally the
	 * h_proto field is in the same place so we just leave it alone and
	 * overwrite the remaining fields.
	 */
	packet = (struct vl600_pkt_hdr *) skb->data;
	/* The VL600 wants IPv6 packets to have an IPv4 ethertype
	 * Since this modem only supports IPv4 and IPv6, just set all
	 * frames to 0x0800 (ETH_P_IP)
	 */
	packet->h_proto = htons(ETH_P_IP);
	memset(&packet->dummy, 0, sizeof(packet->dummy));
	packet->len = cpu_to_le32(orig_len);

	frame = skb_push(skb, sizeof(*frame));
	memset(frame, 0, sizeof(*frame));
	frame->len = cpu_to_le32(full_len);
	frame->serial = cpu_to_le32(serial++);
	frame->pkt_cnt = cpu_to_le32(1);

	if (skb->len < full_len) /* Pad */
		skb_put(skb, full_len - skb->len);

	return skb;
}