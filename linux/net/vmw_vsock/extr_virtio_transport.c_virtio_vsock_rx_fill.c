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
struct virtqueue {scalar_t__ num_free; } ;
struct virtio_vsock_pkt {int buf_len; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  hdr; } ;
struct virtio_vsock {scalar_t__ rx_buf_nr; scalar_t__ rx_buf_max_nr; struct virtqueue** vqs; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VIRTIO_VSOCK_DEFAULT_RX_BUF_SIZE ; 
 size_t VSOCK_VQ_RX ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct virtio_vsock_pkt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  virtio_transport_free_pkt (struct virtio_vsock_pkt*) ; 
 int virtqueue_add_sgs (struct virtqueue*,struct scatterlist**,int /*<<< orphan*/ ,int,struct virtio_vsock_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static void virtio_vsock_rx_fill(struct virtio_vsock *vsock)
{
	int buf_len = VIRTIO_VSOCK_DEFAULT_RX_BUF_SIZE;
	struct virtio_vsock_pkt *pkt;
	struct scatterlist hdr, buf, *sgs[2];
	struct virtqueue *vq;
	int ret;

	vq = vsock->vqs[VSOCK_VQ_RX];

	do {
		pkt = kzalloc(sizeof(*pkt), GFP_KERNEL);
		if (!pkt)
			break;

		pkt->buf = kmalloc(buf_len, GFP_KERNEL);
		if (!pkt->buf) {
			virtio_transport_free_pkt(pkt);
			break;
		}

		pkt->buf_len = buf_len;
		pkt->len = buf_len;

		sg_init_one(&hdr, &pkt->hdr, sizeof(pkt->hdr));
		sgs[0] = &hdr;

		sg_init_one(&buf, pkt->buf, buf_len);
		sgs[1] = &buf;
		ret = virtqueue_add_sgs(vq, sgs, 0, 2, pkt, GFP_KERNEL);
		if (ret) {
			virtio_transport_free_pkt(pkt);
			break;
		}
		vsock->rx_buf_nr++;
	} while (vq->num_free);
	if (vsock->rx_buf_nr > vsock->rx_buf_max_nr)
		vsock->rx_buf_max_nr = vsock->rx_buf_nr;
	virtqueue_kick(vq);
}