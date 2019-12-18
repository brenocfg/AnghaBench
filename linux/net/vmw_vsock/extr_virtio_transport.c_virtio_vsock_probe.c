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
typedef  int /*<<< orphan*/  vq_callback_t ;
struct virtio_vsock {int tx_run; int rx_run; int event_run; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  loopback_work; int /*<<< orphan*/  send_pkt_work; int /*<<< orphan*/  event_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  loopback_list; int /*<<< orphan*/  loopback_list_lock; int /*<<< orphan*/  send_pkt_list; int /*<<< orphan*/  send_pkt_list_lock; int /*<<< orphan*/  queued_replies; scalar_t__ rx_buf_max_nr; scalar_t__ rx_buf_nr; int /*<<< orphan*/  vqs; struct virtio_device* vdev; } ;
struct virtio_device {struct virtio_vsock* priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSOCK_VQ_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtio_vsock*) ; 
 struct virtio_vsock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct virtio_vsock*) ; 
 scalar_t__ rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_virtio_vsock ; 
 int /*<<< orphan*/  the_virtio_vsock_mutex ; 
 int virtio_find_vqs (struct virtio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_transport_event_work ; 
 int /*<<< orphan*/  virtio_transport_loopback_work ; 
 int /*<<< orphan*/  virtio_transport_rx_work ; 
 int /*<<< orphan*/  virtio_transport_send_pkt_work ; 
 int /*<<< orphan*/  virtio_transport_tx_work ; 
 int /*<<< orphan*/ * virtio_vsock_event_done ; 
 int /*<<< orphan*/  virtio_vsock_event_fill (struct virtio_vsock*) ; 
 int /*<<< orphan*/ * virtio_vsock_rx_done ; 
 int /*<<< orphan*/  virtio_vsock_rx_fill (struct virtio_vsock*) ; 
 int /*<<< orphan*/ * virtio_vsock_tx_done ; 
 int /*<<< orphan*/  virtio_vsock_update_guest_cid (struct virtio_vsock*) ; 

__attribute__((used)) static int virtio_vsock_probe(struct virtio_device *vdev)
{
	vq_callback_t *callbacks[] = {
		virtio_vsock_rx_done,
		virtio_vsock_tx_done,
		virtio_vsock_event_done,
	};
	static const char * const names[] = {
		"rx",
		"tx",
		"event",
	};
	struct virtio_vsock *vsock = NULL;
	int ret;

	ret = mutex_lock_interruptible(&the_virtio_vsock_mutex);
	if (ret)
		return ret;

	/* Only one virtio-vsock device per guest is supported */
	if (rcu_dereference_protected(the_virtio_vsock,
				lockdep_is_held(&the_virtio_vsock_mutex))) {
		ret = -EBUSY;
		goto out;
	}

	vsock = kzalloc(sizeof(*vsock), GFP_KERNEL);
	if (!vsock) {
		ret = -ENOMEM;
		goto out;
	}

	vsock->vdev = vdev;

	ret = virtio_find_vqs(vsock->vdev, VSOCK_VQ_MAX,
			      vsock->vqs, callbacks, names,
			      NULL);
	if (ret < 0)
		goto out;

	virtio_vsock_update_guest_cid(vsock);

	vsock->rx_buf_nr = 0;
	vsock->rx_buf_max_nr = 0;
	atomic_set(&vsock->queued_replies, 0);

	mutex_init(&vsock->tx_lock);
	mutex_init(&vsock->rx_lock);
	mutex_init(&vsock->event_lock);
	spin_lock_init(&vsock->send_pkt_list_lock);
	INIT_LIST_HEAD(&vsock->send_pkt_list);
	spin_lock_init(&vsock->loopback_list_lock);
	INIT_LIST_HEAD(&vsock->loopback_list);
	INIT_WORK(&vsock->rx_work, virtio_transport_rx_work);
	INIT_WORK(&vsock->tx_work, virtio_transport_tx_work);
	INIT_WORK(&vsock->event_work, virtio_transport_event_work);
	INIT_WORK(&vsock->send_pkt_work, virtio_transport_send_pkt_work);
	INIT_WORK(&vsock->loopback_work, virtio_transport_loopback_work);

	mutex_lock(&vsock->tx_lock);
	vsock->tx_run = true;
	mutex_unlock(&vsock->tx_lock);

	mutex_lock(&vsock->rx_lock);
	virtio_vsock_rx_fill(vsock);
	vsock->rx_run = true;
	mutex_unlock(&vsock->rx_lock);

	mutex_lock(&vsock->event_lock);
	virtio_vsock_event_fill(vsock);
	vsock->event_run = true;
	mutex_unlock(&vsock->event_lock);

	vdev->priv = vsock;
	rcu_assign_pointer(the_virtio_vsock, vsock);

	mutex_unlock(&the_virtio_vsock_mutex);
	return 0;

out:
	kfree(vsock);
	mutex_unlock(&the_virtio_vsock_mutex);
	return ret;
}