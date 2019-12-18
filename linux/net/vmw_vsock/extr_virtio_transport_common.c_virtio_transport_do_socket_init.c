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
struct vsock_sock {struct virtio_vsock_sock* trans; } ;
struct virtio_vsock_sock {int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_alloc; int /*<<< orphan*/  buf_size_max; int /*<<< orphan*/  buf_size_min; int /*<<< orphan*/  peer_buf_alloc; struct vsock_sock* vsk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_DEFAULT_BUF_SIZE ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_DEFAULT_MAX_BUF_SIZE ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_DEFAULT_MIN_BUF_SIZE ; 
 struct virtio_vsock_sock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int virtio_transport_do_socket_init(struct vsock_sock *vsk,
				    struct vsock_sock *psk)
{
	struct virtio_vsock_sock *vvs;

	vvs = kzalloc(sizeof(*vvs), GFP_KERNEL);
	if (!vvs)
		return -ENOMEM;

	vsk->trans = vvs;
	vvs->vsk = vsk;
	if (psk) {
		struct virtio_vsock_sock *ptrans = psk->trans;

		vvs->buf_size	= ptrans->buf_size;
		vvs->buf_size_min = ptrans->buf_size_min;
		vvs->buf_size_max = ptrans->buf_size_max;
		vvs->peer_buf_alloc = ptrans->peer_buf_alloc;
	} else {
		vvs->buf_size = VIRTIO_VSOCK_DEFAULT_BUF_SIZE;
		vvs->buf_size_min = VIRTIO_VSOCK_DEFAULT_MIN_BUF_SIZE;
		vvs->buf_size_max = VIRTIO_VSOCK_DEFAULT_MAX_BUF_SIZE;
	}

	vvs->buf_alloc = vvs->buf_size;

	spin_lock_init(&vvs->rx_lock);
	spin_lock_init(&vvs->tx_lock);
	INIT_LIST_HEAD(&vvs->rx_queue);

	return 0;
}