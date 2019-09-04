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
struct vhost_virtqueue {int /*<<< orphan*/  mutex; struct vhost_net_ubuf_ref* private_data; } ;
struct vhost_net_virtqueue {struct vhost_net_ubuf_ref* ubufs; int /*<<< orphan*/  rx_ring; struct vhost_virtqueue vq; } ;
struct vhost_net_ubuf_ref {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct vhost_net {int tx_flush; TYPE_1__ dev; scalar_t__ tx_zcopy_err; scalar_t__ tx_packets; struct vhost_net_virtqueue* vqs; } ;
typedef  struct vhost_net_ubuf_ref socket ;

/* Variables and functions */
 int EFAULT ; 
 int ENOBUFS ; 
 scalar_t__ IS_ERR (struct vhost_net_ubuf_ref*) ; 
 int PTR_ERR (struct vhost_net_ubuf_ref*) ; 
 unsigned int VHOST_NET_VQ_MAX ; 
 unsigned int VHOST_NET_VQ_RX ; 
 struct vhost_net_ubuf_ref* get_socket (int) ; 
 int /*<<< orphan*/  get_tap_ptr_ring (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockfd_put (struct vhost_net_ubuf_ref*) ; 
 int vhost_dev_check_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_net_buf_unproduce (struct vhost_net_virtqueue*) ; 
 int /*<<< orphan*/  vhost_net_disable_vq (struct vhost_net*,struct vhost_virtqueue*) ; 
 int vhost_net_enable_vq (struct vhost_net*,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_net_flush_vq (struct vhost_net*,unsigned int) ; 
 struct vhost_net_ubuf_ref* vhost_net_ubuf_alloc (struct vhost_virtqueue*,int) ; 
 int /*<<< orphan*/  vhost_net_ubuf_put_wait_and_free (struct vhost_net_ubuf_ref*) ; 
 scalar_t__ vhost_sock_zcopy (struct vhost_net_ubuf_ref*) ; 
 int /*<<< orphan*/  vhost_vq_access_ok (struct vhost_virtqueue*) ; 
 int vhost_vq_init_access (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_zerocopy_signal_used (struct vhost_net*,struct vhost_virtqueue*) ; 

__attribute__((used)) static long vhost_net_set_backend(struct vhost_net *n, unsigned index, int fd)
{
	struct socket *sock, *oldsock;
	struct vhost_virtqueue *vq;
	struct vhost_net_virtqueue *nvq;
	struct vhost_net_ubuf_ref *ubufs, *oldubufs = NULL;
	int r;

	mutex_lock(&n->dev.mutex);
	r = vhost_dev_check_owner(&n->dev);
	if (r)
		goto err;

	if (index >= VHOST_NET_VQ_MAX) {
		r = -ENOBUFS;
		goto err;
	}
	vq = &n->vqs[index].vq;
	nvq = &n->vqs[index];
	mutex_lock(&vq->mutex);

	/* Verify that ring has been setup correctly. */
	if (!vhost_vq_access_ok(vq)) {
		r = -EFAULT;
		goto err_vq;
	}
	sock = get_socket(fd);
	if (IS_ERR(sock)) {
		r = PTR_ERR(sock);
		goto err_vq;
	}

	/* start polling new socket */
	oldsock = vq->private_data;
	if (sock != oldsock) {
		ubufs = vhost_net_ubuf_alloc(vq,
					     sock && vhost_sock_zcopy(sock));
		if (IS_ERR(ubufs)) {
			r = PTR_ERR(ubufs);
			goto err_ubufs;
		}

		vhost_net_disable_vq(n, vq);
		vq->private_data = sock;
		vhost_net_buf_unproduce(nvq);
		r = vhost_vq_init_access(vq);
		if (r)
			goto err_used;
		r = vhost_net_enable_vq(n, vq);
		if (r)
			goto err_used;
		if (index == VHOST_NET_VQ_RX)
			nvq->rx_ring = get_tap_ptr_ring(fd);

		oldubufs = nvq->ubufs;
		nvq->ubufs = ubufs;

		n->tx_packets = 0;
		n->tx_zcopy_err = 0;
		n->tx_flush = false;
	}

	mutex_unlock(&vq->mutex);

	if (oldubufs) {
		vhost_net_ubuf_put_wait_and_free(oldubufs);
		mutex_lock(&vq->mutex);
		vhost_zerocopy_signal_used(n, vq);
		mutex_unlock(&vq->mutex);
	}

	if (oldsock) {
		vhost_net_flush_vq(n, index);
		sockfd_put(oldsock);
	}

	mutex_unlock(&n->dev.mutex);
	return 0;

err_used:
	vq->private_data = oldsock;
	vhost_net_enable_vq(n, vq);
	if (ubufs)
		vhost_net_ubuf_put_wait_and_free(ubufs);
err_ubufs:
	if (sock)
		sockfd_put(sock);
err_vq:
	mutex_unlock(&vq->mutex);
err:
	mutex_unlock(&n->dev.mutex);
	return r;
}