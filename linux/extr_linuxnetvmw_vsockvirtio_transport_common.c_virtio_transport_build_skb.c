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
struct TYPE_2__ {int /*<<< orphan*/  op; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_cid; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_cid; } ;
struct virtio_vsock_pkt {int len; TYPE_1__* buf; TYPE_1__ hdr; } ;
struct sk_buff {int dummy; } ;
struct af_vsockmon_hdr {void* op; int /*<<< orphan*/  reserved; void* len; void* transport; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_cid; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_cid; } ;

/* Variables and functions */
 int AF_VSOCK_OP_CONNECT ; 
 int AF_VSOCK_OP_CONTROL ; 
 int AF_VSOCK_OP_DISCONNECT ; 
 int AF_VSOCK_OP_PAYLOAD ; 
 int AF_VSOCK_OP_UNKNOWN ; 
 int AF_VSOCK_TRANSPORT_VIRTIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  VIRTIO_VSOCK_OP_CREDIT_REQUEST 134 
#define  VIRTIO_VSOCK_OP_CREDIT_UPDATE 133 
#define  VIRTIO_VSOCK_OP_REQUEST 132 
#define  VIRTIO_VSOCK_OP_RESPONSE 131 
#define  VIRTIO_VSOCK_OP_RST 130 
#define  VIRTIO_VSOCK_OP_RW 129 
#define  VIRTIO_VSOCK_OP_SHUTDOWN 128 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct af_vsockmon_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,TYPE_1__*,int) ; 

__attribute__((used)) static struct sk_buff *virtio_transport_build_skb(void *opaque)
{
	struct virtio_vsock_pkt *pkt = opaque;
	struct af_vsockmon_hdr *hdr;
	struct sk_buff *skb;

	skb = alloc_skb(sizeof(*hdr) + sizeof(pkt->hdr) + pkt->len,
			GFP_ATOMIC);
	if (!skb)
		return NULL;

	hdr = skb_put(skb, sizeof(*hdr));

	/* pkt->hdr is little-endian so no need to byteswap here */
	hdr->src_cid = pkt->hdr.src_cid;
	hdr->src_port = pkt->hdr.src_port;
	hdr->dst_cid = pkt->hdr.dst_cid;
	hdr->dst_port = pkt->hdr.dst_port;

	hdr->transport = cpu_to_le16(AF_VSOCK_TRANSPORT_VIRTIO);
	hdr->len = cpu_to_le16(sizeof(pkt->hdr));
	memset(hdr->reserved, 0, sizeof(hdr->reserved));

	switch (le16_to_cpu(pkt->hdr.op)) {
	case VIRTIO_VSOCK_OP_REQUEST:
	case VIRTIO_VSOCK_OP_RESPONSE:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_CONNECT);
		break;
	case VIRTIO_VSOCK_OP_RST:
	case VIRTIO_VSOCK_OP_SHUTDOWN:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_DISCONNECT);
		break;
	case VIRTIO_VSOCK_OP_RW:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_PAYLOAD);
		break;
	case VIRTIO_VSOCK_OP_CREDIT_UPDATE:
	case VIRTIO_VSOCK_OP_CREDIT_REQUEST:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_CONTROL);
		break;
	default:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_UNKNOWN);
		break;
	}

	skb_put_data(skb, &pkt->hdr, sizeof(pkt->hdr));

	if (pkt->len) {
		skb_put_data(skb, pkt->buf, pkt->len);
	}

	return skb;
}