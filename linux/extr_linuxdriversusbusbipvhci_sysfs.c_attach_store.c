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
struct vhci_hcd {struct vhci* vhci; } ;
struct TYPE_8__ {scalar_t__ status; int sockfd; void* tcp_tx; void* tcp_rx; int /*<<< orphan*/  lock; struct socket* tcp_socket; } ;
struct vhci_device {size_t devid; size_t speed; TYPE_4__ ud; } ;
struct vhci {int /*<<< orphan*/  lock; TYPE_2__* vhci_hcd_hs; TYPE_1__* vhci_hcd_ss; } ;
struct usb_hcd {int dummy; } ;
struct socket {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t __u32 ;
struct TYPE_7__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_6__ {struct vhci_device* vdev; } ;
struct TYPE_5__ {struct vhci_device* vdev; } ;

/* Variables and functions */
 size_t EAGAIN ; 
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t USB_SPEED_SUPER ; 
 scalar_t__ VDEV_ST_NOTASSIGNED ; 
 scalar_t__ VDEV_ST_NULL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,size_t,size_t,int) ; 
 struct vhci_hcd* hcd_to_vhci_hcd (struct usb_hcd*) ; 
 void* kthread_get_run (int /*<<< orphan*/ ,TYPE_4__*,char*) ; 
 struct usb_hcd* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 size_t port_to_pdev_nr (size_t) ; 
 size_t port_to_rhport (size_t) ; 
 int /*<<< orphan*/  rh_port_connect (struct vhci_device*,size_t) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sscanf (char const*,char*,size_t*,int*,size_t*,size_t*) ; 
 int usb_speed_string (size_t) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_sysfs (char*,int,size_t,size_t) ; 
 int /*<<< orphan*/  valid_args (size_t*,size_t*,size_t) ; 
 int /*<<< orphan*/  vhci_rx_loop ; 
 int /*<<< orphan*/  vhci_tx_loop ; 
 TYPE_3__* vhcis ; 

__attribute__((used)) static ssize_t attach_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct socket *socket;
	int sockfd = 0;
	__u32 port = 0, pdev_nr = 0, rhport = 0, devid = 0, speed = 0;
	struct usb_hcd *hcd;
	struct vhci_hcd *vhci_hcd;
	struct vhci_device *vdev;
	struct vhci *vhci;
	int err;
	unsigned long flags;

	/*
	 * @rhport: port number of vhci_hcd
	 * @sockfd: socket descriptor of an established TCP connection
	 * @devid: unique device identifier in a remote host
	 * @speed: usb device speed in a remote host
	 */
	if (sscanf(buf, "%u %u %u %u", &port, &sockfd, &devid, &speed) != 4)
		return -EINVAL;
	pdev_nr = port_to_pdev_nr(port);
	rhport = port_to_rhport(port);

	usbip_dbg_vhci_sysfs("port(%u) pdev(%d) rhport(%u)\n",
			     port, pdev_nr, rhport);
	usbip_dbg_vhci_sysfs("sockfd(%u) devid(%u) speed(%u)\n",
			     sockfd, devid, speed);

	/* check received parameters */
	if (!valid_args(&pdev_nr, &rhport, speed))
		return -EINVAL;

	hcd = platform_get_drvdata(vhcis[pdev_nr].pdev);
	if (hcd == NULL) {
		dev_err(dev, "port %d is not ready\n", port);
		return -EAGAIN;
	}

	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	if (speed == USB_SPEED_SUPER)
		vdev = &vhci->vhci_hcd_ss->vdev[rhport];
	else
		vdev = &vhci->vhci_hcd_hs->vdev[rhport];

	/* Extract socket from fd. */
	socket = sockfd_lookup(sockfd, &err);
	if (!socket)
		return -EINVAL;

	/* now need lock until setting vdev status as used */

	/* begin a lock */
	spin_lock_irqsave(&vhci->lock, flags);
	spin_lock(&vdev->ud.lock);

	if (vdev->ud.status != VDEV_ST_NULL) {
		/* end of the lock */
		spin_unlock(&vdev->ud.lock);
		spin_unlock_irqrestore(&vhci->lock, flags);

		sockfd_put(socket);

		dev_err(dev, "port %d already used\n", rhport);
		/*
		 * Will be retried from userspace
		 * if there's another free port.
		 */
		return -EBUSY;
	}

	dev_info(dev, "pdev(%u) rhport(%u) sockfd(%d)\n",
		 pdev_nr, rhport, sockfd);
	dev_info(dev, "devid(%u) speed(%u) speed_str(%s)\n",
		 devid, speed, usb_speed_string(speed));

	vdev->devid         = devid;
	vdev->speed         = speed;
	vdev->ud.sockfd     = sockfd;
	vdev->ud.tcp_socket = socket;
	vdev->ud.status     = VDEV_ST_NOTASSIGNED;

	spin_unlock(&vdev->ud.lock);
	spin_unlock_irqrestore(&vhci->lock, flags);
	/* end the lock */

	vdev->ud.tcp_rx = kthread_get_run(vhci_rx_loop, &vdev->ud, "vhci_rx");
	vdev->ud.tcp_tx = kthread_get_run(vhci_tx_loop, &vdev->ud, "vhci_tx");

	rh_port_connect(vdev, speed);

	return count;
}